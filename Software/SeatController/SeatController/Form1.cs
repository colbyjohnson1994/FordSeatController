using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace SeatController
{
    public partial class Form1 : Form
    {
        private const float _MAXPWM = 100.0f;
        private const float _MINPWM = 0.0f;

        private bool _controllerConnected = false;

        private List<float> coolLookup = new List<float> { 0.0f, 35.0f, 65.0f, 90.0f };
        private List<float> heatLookup = new List<float> { 0.0f, 47.0f, 55.0f, 62.0f };

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

        private Series cshSPSeries = new Series();
        private Series cshTempSeries = new Series();
        private Series bkSPSeries = new Series();
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
            // default the dropdowns
            unitsBox.SelectedIndex = 0;
            heatBox.SelectedIndex = 0;
            coolBox.SelectedIndex = 0;

            // refresh ports
            refreshBtn_Click(sender, e);

            // setup chart datas
            SetupChart("Cushion Controller", ref cshChart, ref cshChartArea);
            SetupSeries("Cushion Setpoint", ref cshSPSeries, cshChart);
            SetupSeries("Cushion Temperature", ref cshTempSeries, cshChart);

            cshChart.Series.Add(cshSPSeries);
            cshChart.Series.Add(cshTempSeries);

            SetupChart("Seat Back Controller", ref bkChart, ref bkChartArea);
            SetupSeries("Seat Back Setpoint", ref bkSPSeries, bkChart);
            SetupSeries("Seat Back Temperature", ref bkTempSeries, bkChart);

            bkChart.Series.Add(bkSPSeries);
            bkChart.Series.Add(bkTempSeries);
        }

        private void readTimer_Tick(object sender, EventArgs e)
        {
            // if the port closes, stop the timer
            if (!controllerPort.IsOpen)
            {
                readTimer.Enabled = false;
                _controllerConnected = false;
                discoBtn.Enabled = false;

                return;
            }

            discoBtn.Enabled = true;

            // read a new line
            try
            {
                while (controllerPort.BytesToRead > 0)
                {
                    string line = controllerPort.ReadLine();

                    // parse this line and display it
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
            string parser = "(\\S+)=(\\S*)";
            Regex rx = new Regex(parser);

            // find matches
            MatchCollection mathces = rx.Matches(data);
            foreach (Match match in mathces) 
            {
                string key = match.Groups[1].Value;
                string val = match.Groups[2].Value;

                Console.WriteLine(key + "=" + val);

                // store the data
                switch(key) 
                {
                    case "DESIRED_HEAT":
                        desiredHeat = float.Parse(val);
                        cshSPSeries.Points.AddXY((DateTime.Now - startTime).TotalSeconds, desiredHeat);
                        bkSPSeries.Points.AddXY((DateTime.Now - startTime).TotalSeconds, desiredHeat);

                        // increment total packet count
                        totalPacketsRcvd += 1;
                        break;
                    case "DESIRED_COOL":
                        desiredCool = float.Parse(val);
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
                        cshTedPerc = (float.Parse(val) / _MAXPWM) *100.0f;
                        break;
                    case "BK_BLOWR_PWM":
                        bkBlwrPerc = (float.Parse(val) / _MAXPWM) *100.0f;
                        break;
                    case "BK_TED_PWM":
                        bkTedPerc = (float.Parse(val) / _MAXPWM) *100.0f;
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
            if (unitsBox.Text == "C")
                return data;
            else
                return (1.8f * data + 32);
        }

        private void updateDisplay()
        {
            coolBox.SelectedIndex = coolLookup.IndexOf(desiredCool);
            heatBox.SelectedIndex = heatLookup.IndexOf(desiredHeat);

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

            // update chart area min x axis
            if (totalPacketsRcvd > graphWidth.Value)
            {
                long xminVal = (long)cshSPSeries.Points[cshSPSeries.Points.Count - 1 - (int)graphWidth.Value].XValue;
                cshChartArea.AxisX.Minimum = xminVal;
                //bkChartArea.AxisX.Minimum = = xminVal;
            }

            bkDisableCB.Checked = bkShutdownHT || bkShutdownLT;
            cshDisableCB.Checked = cshShutdownLT || cshShutdownHT;
        }

        private void refreshBtn_Click(object sender, EventArgs e)
        {
            //clear box
            commBox.Items.Clear();

            // get list of serial ports and add to the comm box drop down
            string[] ports = SerialPort.GetPortNames();
            foreach (string port in ports) { commBox.Items.Add(port); }

            // close connection
            if (controllerPort.IsOpen)
                controllerPort.Close();

            readTimer.Enabled = false;
        }

        private void commBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (commBox.SelectedIndex != -1) 
            {
                // clear all chart data
                cshSPSeries.Points.Clear();
                cshTempSeries.Points.Clear();
                bkSPSeries.Points.Clear();
                bkTempSeries.Points.Clear();

                startTime = DateTime.Now;

                // attempt to connect to this port
                if (controllerPort.IsOpen)
                    controllerPort.Close();

                // start a new connection
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
        }

        private void SetupSeries(String title, ref Series series, Chart chartArea)
        {
            //Series
            series.ChartArea = chartArea.Name + "Area";
            //Series style
            series.Name = title.Replace(" ", "");
            series.ChartType = SeriesChartType.Line;  // type
            series.BorderWidth = 2;
            series.Color = Color.Green;
            series.XValueType = ChartValueType.Int32;//x axis type
            series.YValueType = ChartValueType.Double;//y axis type

            //Marker
            //series.MarkerStyle = MarkerStyle.Star4;
            //series.MarkerSize = 5;
            //series.MarkerStep = 1;
            //series.MarkerColor = Color.Red;
            //series.ToolTip = @"ToolTip";

            //Label
            series.IsValueShownAsLabel = false;
            series.SmartLabelStyle.Enabled = false;
            series.SmartLabelStyle.AllowOutsidePlotArea = LabelOutsidePlotAreaStyle.Yes;
            series.LabelForeColor = Color.Gray;
            series.LabelToolTip = @"LabelToolTip";

            //Empty Point Style 
            DataPointCustomProperties p = new DataPointCustomProperties();
            p.Color = Color.Green;
            series.EmptyPointStyle = p;

            //Legend
            series.LegendText = title;
            series.LegendToolTip = @"LegendToolTip";
        }

        private void SetupChart(String title, ref Chart chart, ref ChartArea chartArea)
        {
            // chartArea
            chartArea = new ChartArea();
            chartArea.Name = chart.Name + "Area";
            chart.ChartAreas.Add(chartArea);
            chartArea.BackColor = Color.Azure;
            chartArea.BackGradientStyle = GradientStyle.HorizontalCenter;
            chartArea.BackHatchStyle = ChartHatchStyle.LargeGrid;
            chartArea.BorderDashStyle = ChartDashStyle.Solid;
            chartArea.BorderWidth = 1;
            chartArea.BorderColor = Color.Red;
            chartArea.ShadowColor = Color.Purple;
            chartArea.ShadowOffset = 0;
            chart.ChartAreas[0].Axes[0].MajorGrid.Enabled = false;//x axis
            chart.ChartAreas[0].Axes[1].MajorGrid.Enabled = false;//y axis

            //Cursor：only apply the top area
            chartArea.CursorX.IsUserEnabled = true;
            chartArea.CursorX.AxisType = AxisType.Primary;//act on primary x axis
            chartArea.CursorX.Interval = 1;
            chartArea.CursorX.LineWidth = 1;
            chartArea.CursorX.LineDashStyle = ChartDashStyle.Dash;
            chartArea.CursorX.IsUserSelectionEnabled = true;
            chartArea.CursorX.SelectionColor = Color.Yellow;
            chartArea.CursorX.AutoScroll = true;

            chartArea.CursorY.IsUserEnabled = true;
            chartArea.CursorY.AxisType = AxisType.Primary;//act on primary y axis
            chartArea.CursorY.Interval = 1;
            chartArea.CursorY.LineWidth = 1;
            chartArea.CursorY.LineDashStyle = ChartDashStyle.Dash;
            chartArea.CursorY.IsUserSelectionEnabled = true;
            chartArea.CursorY.SelectionColor = Color.Yellow;
            chartArea.CursorY.AutoScroll = true;

            // Axis
            chartArea.AxisY.Minimum = -10d;//Y axis Minimum value
            chartArea.AxisY.Title = @"Temperature °C";
            //chartArea.AxisY.Maximum = 100d;//Y axis Maximum value
            chartArea.AxisX.Minimum = 0d; //X axis Minimum value
            chartArea.AxisX.IsLabelAutoFit = true;
            chartArea.AxisX.LabelAutoFitMinFontSize = 5;
            chartArea.AxisX.LabelStyle.Angle = -20;
            chartArea.AxisX.LabelStyle.IsEndLabelVisible = true;//show the last label
            chartArea.AxisX.Interval = 1;
            chartArea.AxisX.IntervalAutoMode = IntervalAutoMode.FixedCount;
            chartArea.AxisX.IntervalType = DateTimeIntervalType.NotSet;
            chartArea.AxisX.Title = @"Time";
            chartArea.AxisX.TextOrientation = TextOrientation.Auto;
            chartArea.AxisX.LineWidth = 2;
            chartArea.AxisX.LineColor = Color.DarkOrchid;
            chartArea.AxisX.Enabled = AxisEnabled.True;
            chartArea.AxisX.ScrollBar = new AxisScrollBar();
        }

        private void discoBtn_Click(object sender, EventArgs e)
        {
            discoBtn.Enabled = false;
            readTimer.Enabled = false;
            _controllerConnected = false;
            controllerPort.Close();
            refreshBtn_Click(sender, e);
        }
    }
}
