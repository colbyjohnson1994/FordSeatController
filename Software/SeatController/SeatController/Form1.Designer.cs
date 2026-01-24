using System.Drawing;

namespace SeatController
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.cshTedPercent = new System.Windows.Forms.ProgressBar();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.cshBlowerPercent = new System.Windows.Forms.ProgressBar();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.bkBlwr = new System.Windows.Forms.TextBox();
            this.cshBlwr = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.bkTed = new System.Windows.Forms.TextBox();
            this.cshTed = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.bkTemp = new System.Windows.Forms.TextBox();
            this.cshTemp = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.unitsBox = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.controllerPort = new System.IO.Ports.SerialPort(this.components);
            this.readTimer = new System.Windows.Forms.Timer(this.components);
            this.commBox = new System.Windows.Forms.ComboBox();
            this.label12 = new System.Windows.Forms.Label();
            this.refreshBtn = new System.Windows.Forms.Button();
            this.label13 = new System.Windows.Forms.Label();
            this.bkBlwrPercent = new System.Windows.Forms.ProgressBar();
            this.label14 = new System.Windows.Forms.Label();
            this.bkTEDPercent = new System.Windows.Forms.ProgressBar();
            this.cshChart = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.bkChart = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.graphWidth = new System.Windows.Forms.NumericUpDown();
            this.label15 = new System.Windows.Forms.Label();
            this.discoBtn = new System.Windows.Forms.Button();
            this.label16 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.cshDisableCB = new System.Windows.Forms.CheckBox();
            this.bkDisableCB = new System.Windows.Forms.CheckBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnCool3 = new System.Windows.Forms.Button();
            this.btnCool2 = new System.Windows.Forms.Button();
            this.btnCool1 = new System.Windows.Forms.Button();
            this.btnCoolOff = new System.Windows.Forms.Button();
            this.coolStatusLabel = new System.Windows.Forms.Label();
            this.coolLED = new System.Windows.Forms.PictureBox();
            this.btnHeat3 = new System.Windows.Forms.Button();
            this.btnHeat2 = new System.Windows.Forms.Button();
            this.btnHeat1 = new System.Windows.Forms.Button();
            this.btnHeatOff = new System.Windows.Forms.Button();
            this.heatStatusLabel = new System.Windows.Forms.Label();
            this.heatLED = new System.Windows.Forms.PictureBox();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.cshChart)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bkChart)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.graphWidth)).BeginInit();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.coolLED)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.heatLED)).BeginInit();
            this.SuspendLayout();
            // 
            // cshTedPercent
            // 
            this.cshTedPercent.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.cshTedPercent.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.cshTedPercent.ForeColor = System.Drawing.Color.LimeGreen;
            this.cshTedPercent.Location = new System.Drawing.Point(15, 376);
            this.cshTedPercent.Margin = new System.Windows.Forms.Padding(6);
            this.cshTedPercent.Name = "cshTedPercent";
            this.cshTedPercent.Size = new System.Drawing.Size(554, 42);
            this.cshTedPercent.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.cshTedPercent.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.Color.LightGray;
            this.label1.Location = new System.Drawing.Point(17, 341);
            this.label1.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(258, 24);
            this.label1.TabIndex = 1;
            this.label1.Text = "Cushion TED Control Percent";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.ForeColor = System.Drawing.Color.LightGray;
            this.label2.Location = new System.Drawing.Point(17, 430);
            this.label2.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(278, 24);
            this.label2.TabIndex = 3;
            this.label2.Text = "Cushion Blower Control Percent";
            // 
            // cshBlowerPercent
            // 
            this.cshBlowerPercent.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.cshBlowerPercent.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.cshBlowerPercent.ForeColor = System.Drawing.Color.LimeGreen;
            this.cshBlowerPercent.Location = new System.Drawing.Point(15, 465);
            this.cshBlowerPercent.Margin = new System.Windows.Forms.Padding(6);
            this.cshBlowerPercent.Name = "cshBlowerPercent";
            this.cshBlowerPercent.Size = new System.Drawing.Size(554, 42);
            this.cshBlowerPercent.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.cshBlowerPercent.TabIndex = 2;
            // 
            // groupBox2
            // 
            this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(30)))), ((int)(((byte)(30)))), ((int)(((byte)(30)))));
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.bkBlwr);
            this.groupBox2.Controls.Add(this.cshBlwr);
            this.groupBox2.Controls.Add(this.label10);
            this.groupBox2.Controls.Add(this.label11);
            this.groupBox2.Controls.Add(this.bkTed);
            this.groupBox2.Controls.Add(this.cshTed);
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Controls.Add(this.label9);
            this.groupBox2.Controls.Add(this.bkTemp);
            this.groupBox2.Controls.Add(this.cshTemp);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox2.ForeColor = System.Drawing.Color.LightGray;
            this.groupBox2.Location = new System.Drawing.Point(21, 198);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(547, 136);
            this.groupBox2.TabIndex = 6;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Data";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.ForeColor = System.Drawing.Color.LightGray;
            this.label3.Location = new System.Drawing.Point(426, 78);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(85, 17);
            this.label3.TabIndex = 14;
            this.label3.Text = "Back Blower";
            // 
            // bkBlwr
            // 
            this.bkBlwr.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.bkBlwr.ForeColor = System.Drawing.Color.White;
            this.bkBlwr.Location = new System.Drawing.Point(429, 98);
            this.bkBlwr.Name = "bkBlwr";
            this.bkBlwr.ReadOnly = true;
            this.bkBlwr.Size = new System.Drawing.Size(100, 23);
            this.bkBlwr.TabIndex = 13;
            this.bkBlwr.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // cshBlwr
            // 
            this.cshBlwr.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.cshBlwr.ForeColor = System.Drawing.Color.White;
            this.cshBlwr.Location = new System.Drawing.Point(289, 98);
            this.cshBlwr.Name = "cshBlwr";
            this.cshBlwr.ReadOnly = true;
            this.cshBlwr.Size = new System.Drawing.Size(100, 23);
            this.cshBlwr.TabIndex = 12;
            this.cshBlwr.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.ForeColor = System.Drawing.Color.LightGray;
            this.label10.Location = new System.Drawing.Point(289, 78);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(105, 17);
            this.label10.TabIndex = 11;
            this.label10.Text = "Cushion Blower";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.ForeColor = System.Drawing.Color.LightGray;
            this.label11.Location = new System.Drawing.Point(289, 99);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(0, 17);
            this.label11.TabIndex = 10;
            // 
            // bkTed
            // 
            this.bkTed.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.bkTed.ForeColor = System.Drawing.Color.White;
            this.bkTed.Location = new System.Drawing.Point(147, 98);
            this.bkTed.Name = "bkTed";
            this.bkTed.ReadOnly = true;
            this.bkTed.Size = new System.Drawing.Size(100, 23);
            this.bkTed.TabIndex = 9;
            this.bkTed.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // cshTed
            // 
            this.cshTed.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.cshTed.ForeColor = System.Drawing.Color.White;
            this.cshTed.Location = new System.Drawing.Point(7, 98);
            this.cshTed.Name = "cshTed";
            this.cshTed.ReadOnly = true;
            this.cshTed.Size = new System.Drawing.Size(100, 23);
            this.cshTed.TabIndex = 8;
            this.cshTed.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.ForeColor = System.Drawing.Color.LightGray;
            this.label8.Location = new System.Drawing.Point(146, 78);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(132, 17);
            this.label8.TabIndex = 7;
            this.label8.Text = "Seatback TED Perc";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.ForeColor = System.Drawing.Color.LightGray;
            this.label9.Location = new System.Drawing.Point(7, 78);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(124, 17);
            this.label9.TabIndex = 6;
            this.label9.Text = "Cushion TED Perc";
            // 
            // bkTemp
            // 
            this.bkTemp.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.bkTemp.ForeColor = System.Drawing.Color.White;
            this.bkTemp.Location = new System.Drawing.Point(146, 40);
            this.bkTemp.Name = "bkTemp";
            this.bkTemp.ReadOnly = true;
            this.bkTemp.Size = new System.Drawing.Size(100, 23);
            this.bkTemp.TabIndex = 5;
            this.bkTemp.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // cshTemp
            // 
            this.cshTemp.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.cshTemp.ForeColor = System.Drawing.Color.White;
            this.cshTemp.Location = new System.Drawing.Point(6, 40);
            this.cshTemp.Name = "cshTemp";
            this.cshTemp.ReadOnly = true;
            this.cshTemp.Size = new System.Drawing.Size(100, 23);
            this.cshTemp.TabIndex = 4;
            this.cshTemp.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.ForeColor = System.Drawing.Color.LightGray;
            this.label5.Location = new System.Drawing.Point(145, 20);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(107, 17);
            this.label5.TabIndex = 3;
            this.label5.Text = "Seatback Temp";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.ForeColor = System.Drawing.Color.LightGray;
            this.label6.Location = new System.Drawing.Point(6, 20);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(99, 17);
            this.label6.TabIndex = 1;
            this.label6.Text = "Cushion Temp";
            // 
            // unitsBox
            // 
            this.unitsBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.unitsBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.unitsBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.unitsBox.ForeColor = System.Drawing.Color.White;
            this.unitsBox.FormattingEnabled = true;
            this.unitsBox.Items.AddRange(new object[] {
            "C",
            "F"});
            this.unitsBox.Location = new System.Drawing.Point(436, 30);
            this.unitsBox.Name = "unitsBox";
            this.unitsBox.Size = new System.Drawing.Size(121, 24);
            this.unitsBox.TabIndex = 6;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.ForeColor = System.Drawing.Color.LightGray;
            this.label7.Location = new System.Drawing.Point(478, 8);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(40, 17);
            this.label7.TabIndex = 5;
            this.label7.Text = "Units";
            // 
            // controllerPort
            // 
            this.controllerPort.DtrEnable = true;
            this.controllerPort.ReadTimeout = 2000;
            this.controllerPort.RtsEnable = true;
            this.controllerPort.WriteTimeout = 2000;
            // 
            // readTimer
            // 
            this.readTimer.Interval = 500;
            this.readTimer.Tick += new System.EventHandler(this.readTimer_Tick);
            // 
            // commBox
            // 
            this.commBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.commBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.commBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.commBox.ForeColor = System.Drawing.Color.White;
            this.commBox.FormattingEnabled = true;
            this.commBox.Location = new System.Drawing.Point(22, 30);
            this.commBox.Name = "commBox";
            this.commBox.Size = new System.Drawing.Size(121, 24);
            this.commBox.TabIndex = 8;
            this.commBox.SelectedIndexChanged += new System.EventHandler(this.commBox_SelectedIndexChanged);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label12.ForeColor = System.Drawing.Color.LightGray;
            this.label12.Location = new System.Drawing.Point(45, 7);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(76, 17);
            this.label12.TabIndex = 9;
            this.label12.Text = "COM Ports";
            // 
            // refreshBtn
            // 
            this.refreshBtn.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.refreshBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.refreshBtn.ForeColor = System.Drawing.Color.White;
            this.refreshBtn.Location = new System.Drawing.Point(149, 12);
            this.refreshBtn.Name = "refreshBtn";
            this.refreshBtn.Size = new System.Drawing.Size(90, 42);
            this.refreshBtn.TabIndex = 10;
            this.refreshBtn.Text = "Refresh Ports";
            this.refreshBtn.UseVisualStyleBackColor = false;
            this.refreshBtn.Click += new System.EventHandler(this.refreshBtn_Click);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.ForeColor = System.Drawing.Color.LightGray;
            this.label13.Location = new System.Drawing.Point(17, 605);
            this.label13.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(285, 24);
            this.label13.TabIndex = 14;
            this.label13.Text = "Seatback Blower Control Percent";
            // 
            // bkBlwrPercent
            // 
            this.bkBlwrPercent.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.bkBlwrPercent.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.bkBlwrPercent.ForeColor = System.Drawing.Color.LimeGreen;
            this.bkBlwrPercent.Location = new System.Drawing.Point(15, 640);
            this.bkBlwrPercent.Margin = new System.Windows.Forms.Padding(6);
            this.bkBlwrPercent.Name = "bkBlwrPercent";
            this.bkBlwrPercent.Size = new System.Drawing.Size(554, 42);
            this.bkBlwrPercent.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.bkBlwrPercent.TabIndex = 13;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.ForeColor = System.Drawing.Color.LightGray;
            this.label14.Location = new System.Drawing.Point(17, 516);
            this.label14.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(265, 24);
            this.label14.TabIndex = 12;
            this.label14.Text = "Seatback TED Control Percent";
            // 
            // bkTEDPercent
            // 
            this.bkTEDPercent.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.bkTEDPercent.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.bkTEDPercent.ForeColor = System.Drawing.Color.LimeGreen;
            this.bkTEDPercent.Location = new System.Drawing.Point(15, 551);
            this.bkTEDPercent.Margin = new System.Windows.Forms.Padding(6);
            this.bkTEDPercent.Name = "bkTEDPercent";
            this.bkTEDPercent.Size = new System.Drawing.Size(554, 42);
            this.bkTEDPercent.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.bkTEDPercent.TabIndex = 11;
            // 
            // cshChart
            // 
            this.cshChart.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(30)))), ((int)(((byte)(30)))), ((int)(((byte)(30)))));
            this.cshChart.BorderlineColor = System.Drawing.Color.DimGray;
            this.cshChart.Location = new System.Drawing.Point(578, 112);
            this.cshChart.Name = "cshChart";
            this.cshChart.Size = new System.Drawing.Size(446, 255);
            this.cshChart.TabIndex = 15;
            this.cshChart.Text = "Cushion Temperature";
            // 
            // bkChart
            // 
            this.bkChart.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(30)))), ((int)(((byte)(30)))), ((int)(((byte)(30)))));
            this.bkChart.BorderlineColor = System.Drawing.Color.DimGray;
            this.bkChart.Location = new System.Drawing.Point(578, 414);
            this.bkChart.Name = "bkChart";
            this.bkChart.Size = new System.Drawing.Size(446, 255);
            this.bkChart.TabIndex = 16;
            this.bkChart.Text = "Cushion Temperature";
            // 
            // graphWidth
            // 
            this.graphWidth.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.graphWidth.ForeColor = System.Drawing.Color.White;
            this.graphWidth.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.graphWidth.Location = new System.Drawing.Point(904, 25);
            this.graphWidth.Maximum = new decimal(new int[] {
            1050,
            0,
            0,
            0});
            this.graphWidth.Minimum = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.graphWidth.Name = "graphWidth";
            this.graphWidth.Size = new System.Drawing.Size(120, 29);
            this.graphWidth.TabIndex = 17;
            this.graphWidth.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.graphWidth.Value = new decimal(new int[] {
            50,
            0,
            0,
            0});
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label15.ForeColor = System.Drawing.Color.LightGray;
            this.label15.Location = new System.Drawing.Point(773, 30);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(125, 17);
            this.label15.TabIndex = 18;
            this.label15.Text = "Graph Data Points";
            // 
            // discoBtn
            // 
            this.discoBtn.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.discoBtn.Enabled = false;
            this.discoBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.discoBtn.ForeColor = System.Drawing.Color.White;
            this.discoBtn.Location = new System.Drawing.Point(245, 12);
            this.discoBtn.Name = "discoBtn";
            this.discoBtn.Size = new System.Drawing.Size(90, 42);
            this.discoBtn.TabIndex = 19;
            this.discoBtn.Text = "Disconnect";
            this.discoBtn.UseVisualStyleBackColor = false;
            this.discoBtn.Click += new System.EventHandler(this.discoBtn_Click);
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.ForeColor = System.Drawing.Color.LightGray;
            this.label16.Location = new System.Drawing.Point(578, 85);
            this.label16.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(145, 24);
            this.label16.TabIndex = 20;
            this.label16.Text = "Cushion Control";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.ForeColor = System.Drawing.Color.LightGray;
            this.label17.Location = new System.Drawing.Point(581, 383);
            this.label17.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(152, 24);
            this.label17.TabIndex = 21;
            this.label17.Text = "Seatback Control";
            // 
            // cshDisableCB
            // 
            this.cshDisableCB.AutoSize = true;
            this.cshDisableCB.ForeColor = System.Drawing.Color.LightGray;
            this.cshDisableCB.Location = new System.Drawing.Point(440, 340);
            this.cshDisableCB.Name = "cshDisableCB";
            this.cshDisableCB.Size = new System.Drawing.Size(102, 28);
            this.cshDisableCB.TabIndex = 22;
            this.cshDisableCB.Text = "Disabled";
            this.cshDisableCB.UseVisualStyleBackColor = true;
            // 
            // bkDisableCB
            // 
            this.bkDisableCB.AutoSize = true;
            this.bkDisableCB.ForeColor = System.Drawing.Color.LightGray;
            this.bkDisableCB.Location = new System.Drawing.Point(440, 516);
            this.bkDisableCB.Name = "bkDisableCB";
            this.bkDisableCB.Size = new System.Drawing.Size(102, 28);
            this.bkDisableCB.TabIndex = 24;
            this.bkDisableCB.Text = "Disabled";
            this.bkDisableCB.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(30)))), ((int)(((byte)(30)))), ((int)(((byte)(30)))));
            this.groupBox1.Controls.Add(this.btnCool3);
            this.groupBox1.Controls.Add(this.btnCool2);
            this.groupBox1.Controls.Add(this.btnCool1);
            this.groupBox1.Controls.Add(this.btnCoolOff);
            this.groupBox1.Controls.Add(this.coolStatusLabel);
            this.groupBox1.Controls.Add(this.coolLED);
            this.groupBox1.Controls.Add(this.btnHeat3);
            this.groupBox1.Controls.Add(this.btnHeat2);
            this.groupBox1.Controls.Add(this.btnHeat1);
            this.groupBox1.Controls.Add(this.btnHeatOff);
            this.groupBox1.Controls.Add(this.heatStatusLabel);
            this.groupBox1.Controls.Add(this.heatLED);
            this.groupBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox1.ForeColor = System.Drawing.Color.LightGray;
            this.groupBox1.Location = new System.Drawing.Point(22, 60);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(547, 132);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Mode Control";
            // 
            // btnCool3
            // 
            this.btnCool3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.btnCool3.ForeColor = System.Drawing.Color.White;
            this.btnCool3.Location = new System.Drawing.Point(372, 73);
            this.btnCool3.Name = "btnCool3";
            this.btnCool3.Size = new System.Drawing.Size(75, 23);
            this.btnCool3.TabIndex = 11;
            this.btnCool3.Text = "Cool 3";
            this.btnCool3.UseVisualStyleBackColor = false;
            this.btnCool3.Click += new System.EventHandler(this.btnCool3_Click);
            // 
            // btnCool2
            // 
            this.btnCool2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.btnCool2.ForeColor = System.Drawing.Color.White;
            this.btnCool2.Location = new System.Drawing.Point(291, 73);
            this.btnCool2.Name = "btnCool2";
            this.btnCool2.Size = new System.Drawing.Size(75, 23);
            this.btnCool2.TabIndex = 10;
            this.btnCool2.Text = "Cool 2";
            this.btnCool2.UseVisualStyleBackColor = false;
            this.btnCool2.Click += new System.EventHandler(this.btnCool2_Click);
            // 
            // btnCool1
            // 
            this.btnCool1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.btnCool1.ForeColor = System.Drawing.Color.White;
            this.btnCool1.Location = new System.Drawing.Point(210, 73);
            this.btnCool1.Name = "btnCool1";
            this.btnCool1.Size = new System.Drawing.Size(75, 23);
            this.btnCool1.TabIndex = 9;
            this.btnCool1.Text = "Cool 1";
            this.btnCool1.UseVisualStyleBackColor = false;
            this.btnCool1.Click += new System.EventHandler(this.btnCool1_Click);
            // 
            // btnCoolOff
            // 
            this.btnCoolOff.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.btnCoolOff.ForeColor = System.Drawing.Color.White;
            this.btnCoolOff.Location = new System.Drawing.Point(129, 73);
            this.btnCoolOff.Name = "btnCoolOff";
            this.btnCoolOff.Size = new System.Drawing.Size(75, 23);
            this.btnCoolOff.TabIndex = 8;
            this.btnCoolOff.Text = "Off";
            this.btnCoolOff.UseVisualStyleBackColor = false;
            this.btnCoolOff.Click += new System.EventHandler(this.btnCoolOff_Click);
            // 
            // coolStatusLabel
            // 
            this.coolStatusLabel.AutoSize = true;
            this.coolStatusLabel.ForeColor = System.Drawing.Color.LightGray;
            this.coolStatusLabel.Location = new System.Drawing.Point(52, 82);
            this.coolStatusLabel.Name = "coolStatusLabel";
            this.coolStatusLabel.Size = new System.Drawing.Size(63, 17);
            this.coolStatusLabel.TabIndex = 3;
            this.coolStatusLabel.Text = "Cool: Off";
            // 
            // coolLED
            // 
            this.coolLED.Location = new System.Drawing.Point(6, 73);
            this.coolLED.Name = "coolLED";
            this.coolLED.Size = new System.Drawing.Size(40, 40);
            this.coolLED.TabIndex = 1;
            this.coolLED.TabStop = false;
            // 
            // btnHeat3
            // 
            this.btnHeat3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.btnHeat3.ForeColor = System.Drawing.Color.White;
            this.btnHeat3.Location = new System.Drawing.Point(372, 27);
            this.btnHeat3.Name = "btnHeat3";
            this.btnHeat3.Size = new System.Drawing.Size(75, 23);
            this.btnHeat3.TabIndex = 7;
            this.btnHeat3.Text = "Heat 3";
            this.btnHeat3.UseVisualStyleBackColor = false;
            this.btnHeat3.Click += new System.EventHandler(this.btnHeat3_Click);
            // 
            // btnHeat2
            // 
            this.btnHeat2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.btnHeat2.ForeColor = System.Drawing.Color.White;
            this.btnHeat2.Location = new System.Drawing.Point(291, 27);
            this.btnHeat2.Name = "btnHeat2";
            this.btnHeat2.Size = new System.Drawing.Size(75, 23);
            this.btnHeat2.TabIndex = 6;
            this.btnHeat2.Text = "Heat 2";
            this.btnHeat2.UseVisualStyleBackColor = false;
            this.btnHeat2.Click += new System.EventHandler(this.btnHeat2_Click);
            // 
            // btnHeat1
            // 
            this.btnHeat1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.btnHeat1.ForeColor = System.Drawing.Color.White;
            this.btnHeat1.Location = new System.Drawing.Point(210, 27);
            this.btnHeat1.Name = "btnHeat1";
            this.btnHeat1.Size = new System.Drawing.Size(75, 23);
            this.btnHeat1.TabIndex = 5;
            this.btnHeat1.Text = "Heat 1";
            this.btnHeat1.UseVisualStyleBackColor = false;
            this.btnHeat1.Click += new System.EventHandler(this.btnHeat1_Click);
            // 
            // btnHeatOff
            // 
            this.btnHeatOff.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.btnHeatOff.ForeColor = System.Drawing.Color.White;
            this.btnHeatOff.Location = new System.Drawing.Point(129, 27);
            this.btnHeatOff.Name = "btnHeatOff";
            this.btnHeatOff.Size = new System.Drawing.Size(75, 23);
            this.btnHeatOff.TabIndex = 4;
            this.btnHeatOff.Text = "Off";
            this.btnHeatOff.UseVisualStyleBackColor = false;
            this.btnHeatOff.Click += new System.EventHandler(this.btnHeatOff_Click);
            // 
            // heatStatusLabel
            // 
            this.heatStatusLabel.AutoSize = true;
            this.heatStatusLabel.ForeColor = System.Drawing.Color.LightGray;
            this.heatStatusLabel.Location = new System.Drawing.Point(52, 36);
            this.heatStatusLabel.Name = "heatStatusLabel";
            this.heatStatusLabel.Size = new System.Drawing.Size(65, 17);
            this.heatStatusLabel.TabIndex = 2;
            this.heatStatusLabel.Text = "Heat: Off";
            // 
            // heatLED
            // 
            this.heatLED.Location = new System.Drawing.Point(6, 27);
            this.heatLED.Name = "heatLED";
            this.heatLED.Size = new System.Drawing.Size(40, 40);
            this.heatLED.TabIndex = 0;
            this.heatLED.TabStop = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 24F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(30)))), ((int)(((byte)(30)))), ((int)(((byte)(30)))));
            this.ClientSize = new System.Drawing.Size(1036, 697);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.bkDisableCB);
            this.Controls.Add(this.cshDisableCB);
            this.Controls.Add(this.label17);
            this.Controls.Add(this.label16);
            this.Controls.Add(this.discoBtn);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.graphWidth);
            this.Controls.Add(this.bkChart);
            this.Controls.Add(this.cshChart);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.bkBlwrPercent);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.bkTEDPercent);
            this.Controls.Add(this.refreshBtn);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.commBox);
            this.Controls.Add(this.unitsBox);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.cshBlowerPercent);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.cshTedPercent);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Margin = new System.Windows.Forms.Padding(6);
            this.MinimumSize = new System.Drawing.Size(597, 736);
            this.Name = "Form1";
            this.ShowIcon = false;
            this.Text = "Seat Back Controller";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.cshChart)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bkChart)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.graphWidth)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.coolLED)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.heatLED)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ProgressBar cshTedPercent;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ProgressBar cshBlowerPercent;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox bkBlwr;
        private System.Windows.Forms.TextBox cshBlwr;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox bkTed;
        private System.Windows.Forms.TextBox cshTed;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox bkTemp;
        private System.Windows.Forms.TextBox cshTemp;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox unitsBox;
        private System.Windows.Forms.Label label7;
        private System.IO.Ports.SerialPort controllerPort;
        private System.Windows.Forms.Timer readTimer;
        private System.Windows.Forms.ComboBox commBox;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Button refreshBtn;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.ProgressBar bkBlwrPercent;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.ProgressBar bkTEDPercent;
        private System.Windows.Forms.DataVisualization.Charting.Chart cshChart;
        private System.Windows.Forms.DataVisualization.Charting.Chart bkChart;
        private System.Windows.Forms.NumericUpDown graphWidth;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Button discoBtn;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.CheckBox cshDisableCB;
        private System.Windows.Forms.CheckBox bkDisableCB;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btnCool3;
        private System.Windows.Forms.Button btnCool2;
        private System.Windows.Forms.Button btnCool1;
        private System.Windows.Forms.Button btnCoolOff;
        private System.Windows.Forms.Label coolStatusLabel;
        private System.Windows.Forms.PictureBox coolLED;
        private System.Windows.Forms.Button btnHeat3;
        private System.Windows.Forms.Button btnHeat2;
        private System.Windows.Forms.Button btnHeat1;
        private System.Windows.Forms.Button btnHeatOff;
        private System.Windows.Forms.Label heatStatusLabel;
        private System.Windows.Forms.PictureBox heatLED;
    }
}