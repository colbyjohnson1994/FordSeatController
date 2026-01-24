using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO.Ports;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace SeatController
{
    public partial class Form1 : Form
    {
        private const float _MAXPWM = 100.0f;
        private string currentMode = "OFF";

        private float desiredCool;
        private float desiredHeat;
        private float bkNtc;
        private float cshNtc;
        private float bkBlwrPerc;
        private float bkTedPerc;
        private float cshBlwrPerc;
        private float cshTedPerc;

        private ChartArea cshChartArea;
        private ChartArea bkChartArea;

        private Series cshHeatSeries = new Series();
        private Series cshCoolSeries = new Series();
        private Series bkHeatSeries = new Series();
        private Series bkCoolSeries = new Series();
        private Series cshTempSeries = new Series();
        private Series bkTempSeries = new Series();

        private bool bkShutdownHT = false;
        private bool cshShutdownHT = false;
        private bool bkShutdownLT = false;
        private bool cshShutdownLT = false;

        private long totalPacketsRcvd = 0;
        private DateTime startTime = DateTime.Now;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            unitsBox.SelectedIndex = 0;
            refreshBtn_Click(sender, e);

            // Setup charts
            SetupChart("Cushion Controller", ref cshChart, ref cshChartArea);
            SetupChart("Seat Back Controller", ref bkChart, ref bkChartArea);

            // Setup series
            SetupSeries("Cushion Heat Setpoint", ref cshHeatSeries, cshChart);
            cshHeatSeries.Color = Color.OrangeRed;
            SetupSeries("Cushion Cool Setpoint", ref cshCoolSeries, cshChart);
            cshCoolSeries.Color = Color.DodgerBlue;
            SetupSeries("Cushion Temperature", ref cshTempSeries, cshChart);

            SetupSeries("Seat Back Heat Setpoint", ref bkHeatSeries, bkChart);
            bkHeatSeries.Color = Color.OrangeRed;
            SetupSeries("Seat Back Cool Setpoint", ref bkCoolSeries, bkChart);
            bkCoolSeries.Color = Color.DodgerBlue;
            SetupSeries("Seat Back Temperature", ref bkTempSeries, bkChart);

            // Add series to charts
            cshChart.Series.Add(cshHeatSeries);
            cshChart.Series.Add(cshCoolSeries);
            cshChart.Series.Add(cshTempSeries);

            bkChart.Series.Add(bkHeatSeries);
            bkChart.Series.Add(bkCoolSeries);
            bkChart.Series.Add(bkTempSeries);

            ApplyDarkGridStyle(cshChart);
            ApplyDarkGridStyle(bkChart);

            cshChart.Invalidate();
            bkChart.Invalidate();
        }

        private void readTimer_Tick(object sender, EventArgs e)
        {
            if (!controllerPort.IsOpen)
            {
                readTimer.Enabled = false;
                discoBtn.Enabled = false;
                return;
            }

            discoBtn.Enabled = true;

            try
            {
                while (controllerPort.BytesToRead > 0)
                {
                    string line = controllerPort.ReadLine();
                    parseData(line);
                    updateDisplay();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private void parseData(string data)
        {
            string parser = @"(\S+)=(\S*)";
            Regex rx = new Regex(parser);
            MatchCollection matches = rx.Matches(data);

            foreach (Match match in matches)
            {
                string key = match.Groups[1].Value;
                string val = match.Groups[2].Value;
                Console.WriteLine($"{key}={val}");

                switch (key)
                {
                    case "DESIRED_MODE":
                        currentMode = val;  // e.g. "HEAT_2", "COOL_1", "OFF"
                        break;

                    case "DESIRED_HEAT":
                        desiredHeat = float.Parse(val);
                        // Still plot if heat is active
                        if (desiredHeat > 0)
                        {
                            double x = (DateTime.Now - startTime).TotalSeconds;
                            cshHeatSeries.Points.AddXY(x, desiredHeat);
                            bkHeatSeries.Points.AddXY(x, desiredHeat);
                        }
                        totalPacketsRcvd += 1;
                        break;

                    case "DESIRED_COOL":
                        desiredCool = float.Parse(val);
                        // Still plot if cool is active
                        if (desiredCool > 0)
                        {
                            double x = (DateTime.Now - startTime).TotalSeconds;
                            cshCoolSeries.Points.AddXY(x, desiredCool);
                            bkCoolSeries.Points.AddXY(x, desiredCool);
                        }
                        break;

                    case "CSH_NTC_AVG":
                        cshNtc = float.Parse(val);
                        cshTempSeries.Points.AddXY((DateTime.Now - startTime).TotalSeconds, cshNtc);
                        break;

                    case "BK_NTC_AVG":
                        bkNtc = float.Parse(val);
                        bkTempSeries.Points.AddXY((DateTime.Now - startTime).TotalSeconds, bkNtc);
                        break;

                    case "CSH_BLOWR_PWM":
                        cshBlwrPerc = (float.Parse(val) / _MAXPWM) * 100.0f;
                        break;

                    case "CSH_TED_PWM":
                        cshTedPerc = (float.Parse(val) / _MAXPWM) * 100.0f;
                        break;

                    case "BK_BLOWR_PWM":
                        bkBlwrPerc = (float.Parse(val) / _MAXPWM) * 100.0f;
                        break;

                    case "BK_TED_PWM":
                        bkTedPerc = (float.Parse(val) / _MAXPWM) * 100.0f;
                        break;

                    case "SHUTDOWN_HT_CUSH":
                        cshShutdownHT = Convert.ToBoolean(int.Parse(val));
                        break;

                    case "SHUTDOWN_HT_BACK":
                        bkShutdownHT = Convert.ToBoolean(int.Parse(val));
                        break;

                    case "SHUTDOWN_LT_CUSH":
                        cshShutdownLT = Convert.ToBoolean(int.Parse(val));
                        break;

                    case "SHUTDOWN_LT_BACK":
                        bkShutdownLT = Convert.ToBoolean(int.Parse(val));
                        break;
                }
            }
        }

        private float toUnits(float data)
        {
            return unitsBox.Text == "C" ? data : (1.8f * data + 32);
        }

        private void updateDisplay()
        {
            cshTemp.Text = toUnits(cshNtc).ToString("n2") + " " + unitsBox.Text;
            bkTemp.Text = toUnits(bkNtc).ToString("n2") + " " + unitsBox.Text;

            cshTed.Text = cshTedPerc.ToString("n0");
            cshBlwr.Text = cshBlwrPerc.ToString("n0");
            bkTed.Text = bkTedPerc.ToString("n0");
            bkBlwr.Text = bkBlwrPerc.ToString("n0");

            cshTedPercent.Value = (int)cshTedPerc;
            bkTEDPercent.Value = (int)bkTedPerc;
            cshBlowerPercent.Value = (int)cshBlwrPerc;
            bkBlwrPercent.Value = (int)bkBlwrPerc;

            UpdateChartXAxisMinimum();

            bkDisableCB.Checked = bkShutdownHT || bkShutdownLT;
            cshDisableCB.Checked = cshShutdownLT || cshShutdownHT;

            // Update mode indicators
            UpdateModeIndicators();
        }

        private void refreshBtn_Click(object sender, EventArgs e)
        {
            commBox.Items.Clear();
            string[] ports = SerialPort.GetPortNames();
            commBox.Items.AddRange(ports);

            if (controllerPort.IsOpen)
                controllerPort.Close();

            readTimer.Enabled = false;
        }

        private void commBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (commBox.SelectedIndex == -1) return;

            cshHeatSeries.Points.Clear();
            cshCoolSeries.Points.Clear();
            cshTempSeries.Points.Clear();
            bkHeatSeries.Points.Clear();
            bkCoolSeries.Points.Clear();
            bkTempSeries.Points.Clear();
            startTime = DateTime.Now;

            if (controllerPort.IsOpen)
                controllerPort.Close();

            controllerPort.PortName = commBox.Text;
            controllerPort.BaudRate = 115200;
            controllerPort.ReadTimeout = 2000;
            controllerPort.WriteTimeout = 2000;

            try
            {
                controllerPort.Open();
                while (!controllerPort.IsOpen) { }
                readTimer.Enabled = true;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }

        private void SetupSeries(string title, ref Series series, Chart chart)
        {
            series.ChartArea = chart.Name + "Area";
            series.Name = title.Replace(" ", "");
            series.ChartType = SeriesChartType.Line;
            series.BorderWidth = 2;
            series.XValueType = ChartValueType.Int32;
            series.YValueType = ChartValueType.Double;
            series.IsValueShownAsLabel = false;
            series.SmartLabelStyle.Enabled = false;
            series.SmartLabelStyle.AllowOutsidePlotArea = LabelOutsidePlotAreaStyle.Yes;
            series.LabelForeColor = Color.Gray;
            series.LegendText = title;
        }

        private void SetupChart(string title, ref Chart chart, ref ChartArea chartArea)
        {
            chartArea = new ChartArea();
            chartArea.Name = chart.Name + "Area";
            chart.ChartAreas.Add(chartArea);

            // Disable background hatch grid (prevents white lines)
            chartArea.BackHatchStyle = ChartHatchStyle.None;

            chartArea.BackColor = Color.FromArgb(30, 30, 30);
            chart.BackColor = Color.FromArgb(30, 30, 30);
            chart.ChartAreas[0].BackColor = Color.FromArgb(30, 30, 30);

            // Dim gray dotted major grids
            chartArea.AxisX.MajorGrid.Enabled = true;
            chartArea.AxisX.MajorGrid.LineColor = Color.FromArgb(60, 60, 60);
            chartArea.AxisX.MajorGrid.LineDashStyle = ChartDashStyle.Dot;
            chartArea.AxisX.MajorGrid.LineWidth = 1;

            chartArea.AxisY.MajorGrid.Enabled = true;
            chartArea.AxisY.MajorGrid.LineColor = Color.FromArgb(60, 60, 60);
            chartArea.AxisY.MajorGrid.LineDashStyle = ChartDashStyle.Dot;
            chartArea.AxisY.MajorGrid.LineWidth = 1;

            // Disable minor grids
            chartArea.AxisX.MinorGrid.Enabled = false;
            chartArea.AxisY.MinorGrid.Enabled = false;

            // Prevent palette overrides
            chart.Palette = ChartColorPalette.None;

            chartArea.BorderDashStyle = ChartDashStyle.Solid;
            chartArea.BorderWidth = 1;
            chartArea.BorderColor = Color.Gray;
            chartArea.ShadowColor = Color.Black;
            chartArea.ShadowOffset = 0;

            chartArea.AxisX.LineColor = Color.Gray;
            chartArea.AxisY.LineColor = Color.Gray;
            chartArea.AxisX.LabelStyle.ForeColor = Color.LightGray;
            chartArea.AxisY.LabelStyle.ForeColor = Color.LightGray;
            chartArea.AxisX.TitleForeColor = Color.LightGray;
            chartArea.AxisY.TitleForeColor = Color.LightGray;

            chartArea.CursorX.IsUserEnabled = true;
            chartArea.CursorX.AxisType = AxisType.Primary;
            chartArea.CursorX.Interval = 1;
            chartArea.CursorX.LineWidth = 1;
            chartArea.CursorX.LineDashStyle = ChartDashStyle.Dash;
            chartArea.CursorX.IsUserSelectionEnabled = true;
            chartArea.CursorX.SelectionColor = Color.Yellow;
            chartArea.CursorX.AutoScroll = true;

            chartArea.CursorY.IsUserEnabled = true;
            chartArea.CursorY.AxisType = AxisType.Primary;
            chartArea.CursorY.Interval = 1;
            chartArea.CursorY.LineWidth = 1;
            chartArea.CursorY.LineDashStyle = ChartDashStyle.Dash;
            chartArea.CursorY.IsUserSelectionEnabled = true;
            chartArea.CursorY.SelectionColor = Color.Yellow;
            chartArea.CursorY.AutoScroll = true;

            chartArea.AxisY.Minimum = -10d;
            chartArea.AxisY.Title = "Temperature °C";
            chartArea.AxisX.Minimum = 0d;
            chartArea.AxisX.IsLabelAutoFit = true;
            chartArea.AxisX.LabelAutoFitMinFontSize = 5;
            chartArea.AxisX.LabelStyle.Angle = -20;
            chartArea.AxisX.LabelStyle.IsEndLabelVisible = true;
            chartArea.AxisX.Interval = 1;
            chartArea.AxisX.IntervalAutoMode = IntervalAutoMode.FixedCount;
            chartArea.AxisX.IntervalType = DateTimeIntervalType.NotSet;
            chartArea.AxisX.Title = "Time";
            chartArea.AxisX.TextOrientation = TextOrientation.Auto;
            chartArea.AxisX.LineWidth = 2;
            chartArea.AxisX.LineColor = Color.Gray;
            chartArea.AxisX.Enabled = AxisEnabled.True;
            chartArea.AxisX.ScrollBar = new AxisScrollBar();
        }

        private void btnHeatOff_Click(object sender, EventArgs e) => SendCommand("HEAT:0");
        private void btnHeat1_Click(object sender, EventArgs e) => SendCommand("HEAT:1");
        private void btnHeat2_Click(object sender, EventArgs e) => SendCommand("HEAT:2");
        private void btnHeat3_Click(object sender, EventArgs e) => SendCommand("HEAT:3");

        private void btnCoolOff_Click(object sender, EventArgs e) => SendCommand("COOL:0");
        private void btnCool1_Click(object sender, EventArgs e) => SendCommand("COOL:1");
        private void btnCool2_Click(object sender, EventArgs e) => SendCommand("COOL:2");
        private void btnCool3_Click(object sender, EventArgs e) => SendCommand("COOL:3");

        private void SendCommand(string cmd)
        {
            if (controllerPort.IsOpen)
                controllerPort.WriteLine(cmd);
        }

        private void discoBtn_Click(object sender, EventArgs e)
        {
            controllerPort.Close();
            readTimer.Enabled = false;
            refreshBtn.Enabled = true;
            discoBtn.Enabled = false;
            commBox.Items.Clear();
            commBox.Text = "";
        }

        private float? GetActiveSetpoint()
        {
            if (desiredHeat > 0) return desiredHeat;
            if (desiredCool > 0) return desiredCool;
            return null;
        }

        private void UpdateChartXAxisMinimum()
        {
            int pointsCount = cshTempSeries.Points.Count; // Use temperature series (always plotted)
            if (pointsCount == 0) return;

            int lookback = (int)graphWidth.Value;
            if (pointsCount > lookback)
            {
                int index = pointsCount - 1 - lookback;
                if (index >= 0)
                {
                    double minX = cshTempSeries.Points[index].XValue;
                    cshChartArea.AxisX.Minimum = minX;
                    bkChartArea.AxisX.Minimum = minX;
                }
            }
            else
            {
                cshChartArea.AxisX.Minimum = 0;
                bkChartArea.AxisX.Minimum = 0;
            }
        }

        private void ApplyDarkGridStyle(Chart chart)
        {
            chart.Palette = ChartColorPalette.None;
        }

        private void UpdateModeIndicators()
        {
            // Default: both off
            heatLED.BackColor = Color.DarkGray;
            coolLED.BackColor = Color.DarkGray;

            heatStatusLabel.Text = "Heat: Off";
            coolStatusLabel.Text = "Cool: Off";

            if (currentMode.StartsWith("HEAT_"))
            {
                // Heat is active
                heatLED.BackColor = Color.OrangeRed;  // or Color.Red, your choice
                int level = int.Parse(currentMode.Substring(5)); // "HEAT_1" → 1
                heatStatusLabel.Text = $"Heat: {level}";

                // Cool is off
                coolLED.BackColor = Color.DarkGray;
                coolStatusLabel.Text = "Cool: Off";
            }
            else if (currentMode.StartsWith("COOL_"))
            {
                // Cool is active
                coolLED.BackColor = Color.DodgerBlue;
                int level = int.Parse(currentMode.Substring(5)); // "COOL_1" → 1
                coolStatusLabel.Text = $"Cool: {level}";

                // Heat is off
                heatLED.BackColor = Color.DarkGray;
                heatStatusLabel.Text = "Heat: Off";
            }
            else // "OFF"
            {
                // Both off
                heatLED.BackColor = Color.DarkGray;
                coolLED.BackColor = Color.DarkGray;
                heatStatusLabel.Text = "Heat: Off";
                coolStatusLabel.Text = "Cool: Off";
            }
        }
    }
}