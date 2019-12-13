namespace RexCam
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.speed = new System.Windows.Forms.TrackBar();
            this.BoxCOM = new System.Windows.Forms.ComboBox();
            this.BoxDevices = new System.Windows.Forms.ComboBox();
            this.valueY = new System.Windows.Forms.Label();
            this.valueX = new System.Windows.Forms.Label();
            this.servoY = new System.Windows.Forms.TrackBar();
            this.servoX = new System.Windows.Forms.TrackBar();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.joystickButton = new System.Windows.Forms.PictureBox();
            this.pictureRotate = new System.Windows.Forms.PictureBox();
            this.arrowLeft = new System.Windows.Forms.PictureBox();
            this.arrowRight = new System.Windows.Forms.PictureBox();
            this.turnRight = new System.Windows.Forms.PictureBox();
            this.turnLeft = new System.Windows.Forms.PictureBox();
            this.COM = new System.Windows.Forms.PictureBox();
            this.arrowDown = new System.Windows.Forms.PictureBox();
            this.arrowUp = new System.Windows.Forms.PictureBox();
            this.pictureVideo = new System.Windows.Forms.PictureBox();
            this.picturePhoto = new System.Windows.Forms.PictureBox();
            this.Laser = new System.Windows.Forms.PictureBox();
            this.LED = new System.Windows.Forms.PictureBox();
            this.VideoBox = new System.Windows.Forms.PictureBox();
            this.pathBox = new System.Windows.Forms.PictureBox();
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.openFolder = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.speed)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.joystickButton)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureRotate)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.arrowLeft)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.arrowRight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.turnRight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.turnLeft)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.COM)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.arrowDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.arrowUp)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureVideo)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picturePhoto)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Laser)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.LED)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.VideoBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pathBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.openFolder)).BeginInit();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.ForeColor = System.Drawing.Color.White;
            this.label2.Location = new System.Drawing.Point(1295, 659);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(40, 20);
            this.label2.TabIndex = 48;
            this.label2.Text = "max";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(1079, 661);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(36, 20);
            this.label1.TabIndex = 47;
            this.label1.Text = "min";
            // 
            // speed
            // 
            this.speed.CausesValidation = false;
            this.speed.Enabled = false;
            this.speed.LargeChange = 1;
            this.speed.Location = new System.Drawing.Point(1073, 625);
            this.speed.Maximum = 124;
            this.speed.Minimum = 44;
            this.speed.Name = "speed";
            this.speed.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.speed.Size = new System.Drawing.Size(270, 48);
            this.speed.SmallChange = 0;
            this.speed.TabIndex = 34;
            this.speed.TabStop = false;
            this.speed.TickStyle = System.Windows.Forms.TickStyle.None;
            this.speed.Value = 120;
            // 
            // BoxCOM
            // 
            this.BoxCOM.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.BoxCOM.FormattingEnabled = true;
            this.BoxCOM.Location = new System.Drawing.Point(865, 693);
            this.BoxCOM.Name = "BoxCOM";
            this.BoxCOM.Size = new System.Drawing.Size(127, 24);
            this.BoxCOM.TabIndex = 33;
            this.BoxCOM.SelectedIndexChanged += new System.EventHandler(this.BoxCOM_SelectedIndexChanged_1);
            this.BoxCOM.MouseClick += new System.Windows.Forms.MouseEventHandler(this.BoxCOM_MouseClick_1);
            // 
            // BoxDevices
            // 
            this.BoxDevices.BackColor = System.Drawing.Color.Black;
            this.BoxDevices.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.BoxDevices.ForeColor = System.Drawing.Color.White;
            this.BoxDevices.FormattingEnabled = true;
            this.BoxDevices.Location = new System.Drawing.Point(10, 693);
            this.BoxDevices.Name = "BoxDevices";
            this.BoxDevices.Size = new System.Drawing.Size(180, 24);
            this.BoxDevices.TabIndex = 36;
            this.BoxDevices.TabStop = false;
            this.BoxDevices.SelectedIndexChanged += new System.EventHandler(this.BoxDevices_SelectedIndexChanged_1);
            this.BoxDevices.MouseClick += new System.Windows.Forms.MouseEventHandler(this.BoxDevices_MouseClick_1);
            // 
            // valueY
            // 
            this.valueY.AutoSize = true;
            this.valueY.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.valueY.ForeColor = System.Drawing.Color.White;
            this.valueY.Location = new System.Drawing.Point(1304, 15);
            this.valueY.Name = "valueY";
            this.valueY.Size = new System.Drawing.Size(19, 20);
            this.valueY.TabIndex = 54;
            this.valueY.Text = "Y";
            // 
            // valueX
            // 
            this.valueX.AutoSize = true;
            this.valueX.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.valueX.ForeColor = System.Drawing.Color.White;
            this.valueX.Location = new System.Drawing.Point(1042, 126);
            this.valueX.Name = "valueX";
            this.valueX.Size = new System.Drawing.Size(20, 20);
            this.valueX.TabIndex = 53;
            this.valueX.Text = "X";
            // 
            // servoY
            // 
            this.servoY.CausesValidation = false;
            this.servoY.Enabled = false;
            this.servoY.LargeChange = 1;
            this.servoY.Location = new System.Drawing.Point(1300, 31);
            this.servoY.Maximum = 0;
            this.servoY.Minimum = -180;
            this.servoY.Name = "servoY";
            this.servoY.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.servoY.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.servoY.Size = new System.Drawing.Size(48, 214);
            this.servoY.SmallChange = 0;
            this.servoY.TabIndex = 52;
            this.servoY.TabStop = false;
            this.servoY.TickStyle = System.Windows.Forms.TickStyle.None;
            this.servoY.Value = -111;
            // 
            // servoX
            // 
            this.servoX.Enabled = false;
            this.servoX.LargeChange = 1;
            this.servoX.Location = new System.Drawing.Point(1060, 124);
            this.servoX.Maximum = 180;
            this.servoX.Name = "servoX";
            this.servoX.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.servoX.Size = new System.Drawing.Size(214, 48);
            this.servoX.SmallChange = 0;
            this.servoX.TabIndex = 51;
            this.servoX.TabStop = false;
            this.servoX.TickStyle = System.Windows.Forms.TickStyle.None;
            this.servoX.Value = 81;
            // 
            // timer
            // 
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // joystickButton
            // 
            this.joystickButton.BackColor = System.Drawing.Color.Black;
            this.joystickButton.Image = global::RexCam.Properties.Resources.LED_OFF;
            this.joystickButton.Location = new System.Drawing.Point(1191, 468);
            this.joystickButton.Name = "joystickButton";
            this.joystickButton.Size = new System.Drawing.Size(37, 34);
            this.joystickButton.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.joystickButton.TabIndex = 50;
            this.joystickButton.TabStop = false;
            // 
            // pictureRotate
            // 
            this.pictureRotate.Image = global::RexCam.Properties.Resources.rotate_off;
            this.pictureRotate.Location = new System.Drawing.Point(501, 693);
            this.pictureRotate.Name = "pictureRotate";
            this.pictureRotate.Size = new System.Drawing.Size(40, 35);
            this.pictureRotate.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureRotate.TabIndex = 49;
            this.pictureRotate.TabStop = false;
            this.pictureRotate.Click += new System.EventHandler(this.pictureRotate_Click);
            // 
            // arrowLeft
            // 
            this.arrowLeft.Image = global::RexCam.Properties.Resources.arrowLeft;
            this.arrowLeft.Location = new System.Drawing.Point(1091, 450);
            this.arrowLeft.Name = "arrowLeft";
            this.arrowLeft.Size = new System.Drawing.Size(75, 70);
            this.arrowLeft.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.arrowLeft.TabIndex = 46;
            this.arrowLeft.TabStop = false;
            // 
            // arrowRight
            // 
            this.arrowRight.Image = global::RexCam.Properties.Resources.arrowRight;
            this.arrowRight.Location = new System.Drawing.Point(1253, 450);
            this.arrowRight.Name = "arrowRight";
            this.arrowRight.Size = new System.Drawing.Size(75, 70);
            this.arrowRight.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.arrowRight.TabIndex = 45;
            this.arrowRight.TabStop = false;
            // 
            // turnRight
            // 
            this.turnRight.Image = global::RexCam.Properties.Resources.turnRight_OFF;
            this.turnRight.Location = new System.Drawing.Point(1043, 382);
            this.turnRight.Name = "turnRight";
            this.turnRight.Size = new System.Drawing.Size(85, 207);
            this.turnRight.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.turnRight.TabIndex = 44;
            this.turnRight.TabStop = false;
            // 
            // turnLeft
            // 
            this.turnLeft.Image = global::RexCam.Properties.Resources.turnLeft_OFF;
            this.turnLeft.Location = new System.Drawing.Point(1288, 382);
            this.turnLeft.Name = "turnLeft";
            this.turnLeft.Size = new System.Drawing.Size(85, 207);
            this.turnLeft.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.turnLeft.TabIndex = 43;
            this.turnLeft.TabStop = false;
            // 
            // COM
            // 
            this.COM.Image = global::RexCam.Properties.Resources.COM_OFF;
            this.COM.Location = new System.Drawing.Point(997, 687);
            this.COM.Name = "COM";
            this.COM.Size = new System.Drawing.Size(38, 37);
            this.COM.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.COM.TabIndex = 42;
            this.COM.TabStop = false;
            // 
            // arrowDown
            // 
            this.arrowDown.Image = global::RexCam.Properties.Resources.arrowDown;
            this.arrowDown.Location = new System.Drawing.Point(1172, 519);
            this.arrowDown.Name = "arrowDown";
            this.arrowDown.Size = new System.Drawing.Size(75, 70);
            this.arrowDown.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.arrowDown.TabIndex = 41;
            this.arrowDown.TabStop = false;
            // 
            // arrowUp
            // 
            this.arrowUp.Image = global::RexCam.Properties.Resources.arrowUp;
            this.arrowUp.Location = new System.Drawing.Point(1172, 382);
            this.arrowUp.Name = "arrowUp";
            this.arrowUp.Size = new System.Drawing.Size(75, 70);
            this.arrowUp.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.arrowUp.TabIndex = 40;
            this.arrowUp.TabStop = false;
            // 
            // pictureVideo
            // 
            this.pictureVideo.Image = global::RexCam.Properties.Resources.camVideo1;
            this.pictureVideo.Location = new System.Drawing.Point(352, 676);
            this.pictureVideo.Name = "pictureVideo";
            this.pictureVideo.Size = new System.Drawing.Size(62, 52);
            this.pictureVideo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureVideo.TabIndex = 39;
            this.pictureVideo.TabStop = false;
            this.pictureVideo.Click += new System.EventHandler(this.pictureVideo_Click);
            // 
            // picturePhoto
            // 
            this.picturePhoto.Image = global::RexCam.Properties.Resources.camPh;
            this.picturePhoto.Location = new System.Drawing.Point(626, 676);
            this.picturePhoto.Name = "picturePhoto";
            this.picturePhoto.Size = new System.Drawing.Size(62, 52);
            this.picturePhoto.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.picturePhoto.TabIndex = 38;
            this.picturePhoto.TabStop = false;
            this.picturePhoto.Click += new System.EventHandler(this.picturePhoto_Click);
            // 
            // Laser
            // 
            this.Laser.BackColor = System.Drawing.Color.Black;
            this.Laser.Image = global::RexCam.Properties.Resources.LED_OFF;
            this.Laser.Location = new System.Drawing.Point(1253, 261);
            this.Laser.Name = "Laser";
            this.Laser.Size = new System.Drawing.Size(75, 70);
            this.Laser.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.Laser.TabIndex = 37;
            this.Laser.TabStop = false;
            // 
            // LED
            // 
            this.LED.BackColor = System.Drawing.Color.Black;
            this.LED.Image = global::RexCam.Properties.Resources.LED_OFF;
            this.LED.Location = new System.Drawing.Point(1091, 261);
            this.LED.Name = "LED";
            this.LED.Size = new System.Drawing.Size(75, 70);
            this.LED.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.LED.TabIndex = 35;
            this.LED.TabStop = false;
            // 
            // VideoBox
            // 
            this.VideoBox.BackColor = System.Drawing.Color.Black;
            this.VideoBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.VideoBox.Image = global::RexCam.Properties.Resources.videoError;
            this.VideoBox.Location = new System.Drawing.Point(10, 18);
            this.VideoBox.Name = "VideoBox";
            this.VideoBox.Size = new System.Drawing.Size(1024, 640);
            this.VideoBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.VideoBox.TabIndex = 31;
            this.VideoBox.TabStop = false;
            // 
            // pathBox
            // 
            this.pathBox.BackColor = System.Drawing.Color.Black;
            this.pathBox.Image = global::RexCam.Properties.Resources.save;
            this.pathBox.Location = new System.Drawing.Point(444, 694);
            this.pathBox.Name = "pathBox";
            this.pathBox.Size = new System.Drawing.Size(40, 30);
            this.pathBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pathBox.TabIndex = 55;
            this.pathBox.TabStop = false;
            this.pathBox.Click += new System.EventHandler(this.pathBox_Click);
            // 
            // openFolder
            // 
            this.openFolder.BackColor = System.Drawing.Color.Black;
            this.openFolder.Image = global::RexCam.Properties.Resources.openFolder;
            this.openFolder.Location = new System.Drawing.Point(556, 693);
            this.openFolder.Name = "openFolder";
            this.openFolder.Size = new System.Drawing.Size(40, 35);
            this.openFolder.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.openFolder.TabIndex = 56;
            this.openFolder.TabStop = false;
            this.openFolder.Click += new System.EventHandler(this.openFolder_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Black;
            this.ClientSize = new System.Drawing.Size(1382, 746);
            this.Controls.Add(this.openFolder);
            this.Controls.Add(this.pathBox);
            this.Controls.Add(this.valueY);
            this.Controls.Add(this.valueX);
            this.Controls.Add(this.servoY);
            this.Controls.Add(this.servoX);
            this.Controls.Add(this.joystickButton);
            this.Controls.Add(this.pictureRotate);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.arrowLeft);
            this.Controls.Add(this.arrowRight);
            this.Controls.Add(this.turnRight);
            this.Controls.Add(this.turnLeft);
            this.Controls.Add(this.speed);
            this.Controls.Add(this.COM);
            this.Controls.Add(this.arrowDown);
            this.Controls.Add(this.arrowUp);
            this.Controls.Add(this.pictureVideo);
            this.Controls.Add(this.picturePhoto);
            this.Controls.Add(this.BoxCOM);
            this.Controls.Add(this.Laser);
            this.Controls.Add(this.LED);
            this.Controls.Add(this.BoxDevices);
            this.Controls.Add(this.VideoBox);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.KeyPreview = true;
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(1400, 793);
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(1400, 793);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "RexCam";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Form1_KeyDown);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.Form1_KeyUp);
            ((System.ComponentModel.ISupportInitialize)(this.speed)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.joystickButton)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureRotate)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.arrowLeft)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.arrowRight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.turnRight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.turnLeft)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.COM)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.arrowDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.arrowUp)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureVideo)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picturePhoto)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Laser)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.LED)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.VideoBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pathBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.openFolder)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox joystickButton;
        private System.Windows.Forms.PictureBox pictureRotate;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.PictureBox arrowLeft;
        private System.Windows.Forms.PictureBox arrowRight;
        private System.Windows.Forms.PictureBox turnRight;
        private System.Windows.Forms.PictureBox turnLeft;
        private System.Windows.Forms.TrackBar speed;
        private System.Windows.Forms.PictureBox COM;
        private System.Windows.Forms.PictureBox arrowDown;
        private System.Windows.Forms.PictureBox arrowUp;
        private System.Windows.Forms.PictureBox pictureVideo;
        private System.Windows.Forms.PictureBox picturePhoto;
        private System.Windows.Forms.ComboBox BoxCOM;
        private System.Windows.Forms.PictureBox Laser;
        private System.Windows.Forms.PictureBox LED;
        private System.Windows.Forms.ComboBox BoxDevices;
        private System.Windows.Forms.PictureBox VideoBox;
        private System.Windows.Forms.Label valueY;
        private System.Windows.Forms.Label valueX;
        private System.Windows.Forms.TrackBar servoY;
        private System.Windows.Forms.TrackBar servoX;
        private System.Windows.Forms.Timer timer;
        private System.IO.Ports.SerialPort serialPort;
        private System.Windows.Forms.PictureBox pathBox;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
        private System.Windows.Forms.PictureBox openFolder;
    }
}

