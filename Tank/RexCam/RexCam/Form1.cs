using System;
using System.Drawing;
using System.IO;
using System.Media;
using System.Windows.Forms;
using AForge.Video;
using Accord.Video.VFW;
using AForge.Video.DirectShow;
using System.IO.Ports;
using AForge.Video.FFMPEG;
using System.Drawing.Imaging;
using System.Diagnostics;

namespace RexCam
{
    public partial class Form1 : Form
    {
        VideoFileWriter writer;
        FilterInfoCollection videoDevices;
        VideoCaptureDevice videoSource;
        SoundPlayer simpleSound;
        Bitmap bitmap;

        bool keyPress = false, rotate = false, videoWrite = false;
        bool up = false, down = false, right = false, left = false, tLeft = false, tRight = false;
        bool W = false, S = false, A = false, D = false, C = false, Z = false, X = false, shift = false, ledPressed = false, laserPressed = false;
        int lastIndexCOM, lastIndexCam;
        int width = 640, height = 420;

        int[] dataArray = new int[12] { 999, 124, 127, 81, 111, 0, 0, 0, 0, 0, 0, 0 };

        string path;

        public Form1()
        {
            InitializeComponent();

            timer.Tick += new EventHandler(timer_Tick);
            timer.Interval = 100;
            timer.Start();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //path = Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
            using (StreamReader output = new StreamReader(Environment.CurrentDirectory + "/path.txt"))
            {
                path = output.ReadLine();
            }

            getCamList();
            getCOMList();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (videoSource != null)
            {
                videoSource.SignalToStop();
                videoSource.WaitForStop();
            }

            if (serialPort.IsOpen)
                serialPort.Close();

            if(videoWrite)
                writer.Close();
        }

        private void video_NewFrame(object sender, NewFrameEventArgs eventArgs)
        {
            try
            {
                bitmap = (Bitmap)eventArgs.Frame.Clone();

                if (rotate)
                    bitmap.RotateFlip(RotateFlipType.Rotate180FlipY);

                VideoBox.Image = bitmap;
            }
            catch (Exception)
            {
                BoxDevices.SelectedIndex = 0;
                VideoBox.Image = Properties.Resources.videoError;
            }
        }

        public void getCamList()
        {
            videoDevices = new FilterInfoCollection(FilterCategory.VideoInputDevice);

            BoxDevices.Items.Add("- not selected -");

            if (videoDevices.Count > 0)
            {
                foreach (FilterInfo device in videoDevices)
                {
                    BoxDevices.Items.Add(device.Name);
                }

                BoxDevices.SelectedIndex = 0;
                lastIndexCam = BoxDevices.SelectedIndex;
            }
        }

        private void BoxDevices_MouseClick_1(object sender, MouseEventArgs e)
        {
            if (videoSource != null)
            {
                videoSource.SignalToStop();
                videoSource.WaitForStop();
            }

            BoxDevices.Items.Clear();
            getCamList();
        }

        private void BoxDevices_SelectedIndexChanged_1(object sender, EventArgs e)
        {
            try
            {
                if (!keyPress)
                {
                    videoDevices = new FilterInfoCollection(FilterCategory.VideoInputDevice);

                    if (videoSource != null)
                    {
                        videoSource.SignalToStop();
                        videoSource.WaitForStop();
                    }

                    if (BoxDevices.SelectedIndex == 0)
                    {
                        VideoBox.Image = Properties.Resources.videoError;
                    }
                    else
                    {
                        videoSource = new VideoCaptureDevice(videoDevices[BoxDevices.SelectedIndex - 1].MonikerString);
                        videoSource.NewFrame += new NewFrameEventHandler(video_NewFrame);
                        videoSource.Start();
                    }
                    lastIndexCam = BoxDevices.SelectedIndex;
                }
                else
                    BoxDevices.SelectedIndex = lastIndexCam;
            }
            catch (Exception)
            {
                BoxDevices.SelectedIndex = 0;
                VideoBox.Image = Properties.Resources.videoError;
            }
        }

        public void getCOMList()
        {
            BoxCOM.Items.Add("- not selected -");

            foreach (string serialPort in SerialPort.GetPortNames())
            {
                BoxCOM.Items.Add(serialPort);
            }

            BoxCOM.SelectedIndex = 0;
            lastIndexCOM = BoxCOM.SelectedIndex;
        }

        private void BoxCOM_MouseClick_1(object sender, MouseEventArgs e)
        {
            COM.Image = Properties.Resources.COM_OFF;

            if (serialPort.IsOpen)
                serialPort.Close();

            BoxCOM.Items.Clear();
            getCOMList();
        }

        private void BoxCOM_SelectedIndexChanged_1(object sender, EventArgs e)
        {
            try
            {
                if (!keyPress)
                {
                    if (serialPort.IsOpen)
                    {
                        serialPort.Close();
                        COM.Image = Properties.Resources.COM_OFF;
                    }

                    if (!serialPort.IsOpen && (string)BoxCOM.SelectedItem != "- not selected -")
                    {
                        serialPort.PortName = ((string)BoxCOM.SelectedItem);
                        serialPort.Open();
                        COM.Image = Properties.Resources.COM_ON;
                    }

                    lastIndexCOM = BoxCOM.SelectedIndex;
                }
                else
                    BoxCOM.SelectedIndex = lastIndexCOM;
            }
            catch (Exception)
            {
                BoxCOM.SelectedIndex = 0;
                COM.Image = Properties.Resources.COM_OFF;
            }
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            keyPress = true;

            if (e.KeyCode == Keys.Up && !down && !shift)
            {
                up = true;
                arrowUp.Image = Properties.Resources.arrowUP_Press;
            }
            else if (e.KeyCode == Keys.Down && !up && !shift)
            {
                down = true;
                arrowDown.Image = Properties.Resources.arrowDown_Press;
            }

            if (e.KeyCode == Keys.Right && !left)
            {
                right = true;
                arrowRight.Image = Properties.Resources.arrowRight_Press;
            }
            else if (e.KeyCode == Keys.Left && !right)
            {
                left = true;
                arrowLeft.Image = Properties.Resources.arrowLeft_Press;
            }

            if (e.KeyCode == (Keys)188 && !tRight)
            {
                tLeft = true;
                turnLeft.Image = Properties.Resources.turnLeft_ON;
            }
            else if (e.KeyCode == (Keys)190 && !tLeft)
            {
                tRight = true;
                turnRight.Image = Properties.Resources.turnRight_ON;
            }

            if (e.KeyCode == Keys.ShiftKey && !down && !up && !shift)
            {
                shift = true;
                joystickButton.Image = Properties.Resources.LED_ON;
            }

            if (e.KeyCode == Keys.D1 && !ledPressed)
            {
                ledPressed = true;
                LED.Image = Properties.Resources.LED_ON;
            }
            else if (e.KeyCode == Keys.D1 && ledPressed)
            {
                ledPressed = false;
                LED.Image = Properties.Resources.LED_OFF;
            }

            if (e.KeyCode == Keys.D2 && !laserPressed)
            {
                laserPressed = true;
                Laser.Image = Properties.Resources.LED_ON;
            }
            else if (e.KeyCode == Keys.D2 && laserPressed)
            {
                laserPressed = false;
                Laser.Image = Properties.Resources.LED_OFF;
            }

            if (e.KeyCode == Keys.W && !S)
                W = true;
            if (e.KeyCode == Keys.S && !W)
                S = true;
            if (e.KeyCode == Keys.A && !D)
                A = true;
            if (e.KeyCode == Keys.D && !A)
                D = true;
            if (e.KeyCode == Keys.C)
                C = true;

            if (e.KeyCode == Keys.Z && !X)
                Z = true;
            if (e.KeyCode == Keys.X && !Z)
                X = true;

            if (e.KeyCode == Keys.Space)
            {
                takePhoto();
            }
            if (e.KeyCode == Keys.Enter)
            {
                takeVideo();
            }
        }

        private void Form1_KeyUp(object sender, KeyEventArgs e)
        {
            keyPress = false;

            if (e.KeyCode == Keys.Up)
            {
                up = false;
                arrowUp.Image = Properties.Resources.arrowUp;
            }

            if (e.KeyCode == Keys.Down)
            {
                down = false;
                arrowDown.Image = Properties.Resources.arrowDown;
            }

            if (e.KeyCode == Keys.Right)
            {
                right = false;
                arrowRight.Image = Properties.Resources.arrowRight;
            }

            if (e.KeyCode == Keys.Left)
            {
                left = false;
                arrowLeft.Image = Properties.Resources.arrowLeft;
            }

            if (e.KeyCode == (Keys)188)
            {
                tLeft = false;
                turnLeft.Image = Properties.Resources.turnLeft_OFF;
            }

            if (e.KeyCode == (Keys)190)
            {
                tRight = false;
                turnRight.Image = Properties.Resources.turnRight_OFF;
            }

            if (e.KeyCode == Keys.ShiftKey && !down && !up && shift)
            {
                shift = false;
                joystickButton.Image = Properties.Resources.LED_OFF;
            }

            if (e.KeyCode == Keys.W)
                W = false;
            if (e.KeyCode == Keys.S)
                S = false;
            if (e.KeyCode == Keys.A)
                A = false;
            if (e.KeyCode == Keys.D)
                D = false;
            if (e.KeyCode == Keys.C)
                C = false;

            if (e.KeyCode == Keys.Z)
                Z = false;
            if (e.KeyCode == Keys.X)
                X = false;
        }

        private void pathBox_Click(object sender, EventArgs e)
        {
            if (folderBrowserDialog1.ShowDialog() == DialogResult.OK)
            {
                path = folderBrowserDialog1.SelectedPath + "\\";

                using (StreamWriter input = new StreamWriter(Environment.CurrentDirectory + "/path.txt"))
                {
                    input.WriteLine(path);
                }
            }
        }

        private void openFolder_Click(object sender, EventArgs e)
        {

            Process.Start(path);
        }

        void takePhoto()
        {
            simpleSound = new SoundPlayer(RexCam.Properties.Resources.click);
            simpleSound.Play();

            if (!Directory.Exists(path))
                Directory.CreateDirectory(path);

            VideoBox.Image.Save(path +  DateTime.Now.ToString("dd MMMM yyyy HH.mm.ss") + ".jpg");
        }

        void takeVideo()
        {
            if(!videoWrite)
            {
                if (!Directory.Exists(path))
                    Directory.CreateDirectory(path);

                writer = new VideoFileWriter();
                writer.Open(path + DateTime.Now.ToString("dd MMMM yyyy HH.mm.ss") + ".avi", width, height, 17, VideoCodec.MPEG4);

                pictureVideo.Image = Properties.Resources.camVideo_ON;
                videoWrite = true;
            }
            else
            {
                writer.Close();
                pictureVideo.Image = Properties.Resources.camVideo1;
                videoWrite = false;
            }
        }

        private void pictureRotate_Click(object sender, EventArgs e)
        {
            if (!rotate)
            {
                pictureRotate.Image = Properties.Resources.rotate_on;
                rotate = true;
            }
            else if (rotate)
            {
                pictureRotate.Image = Properties.Resources.rotate_off;
                rotate = false;
            }
        }

        private void picturePhoto_Click(object sender, EventArgs e)
        {
            takePhoto();
        }

        private void pictureVideo_Click(object sender, EventArgs e)
        {
            takeVideo();
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            if(videoWrite)
            {
                writer.WriteVideoFrame(new Bitmap((Bitmap)VideoBox.Image, width, height));
            }

            if (right)
            {
                if (!shift)
                    dataArray[1] = 255;
                else
                    dataArray[1] = 124 + speed.Value;
            }
            if (left)
            {
                if (!shift)
                    dataArray[1] = 0;
                else
                    dataArray[1] = 124 - speed.Value;
            }
            if (!left && !right)
                dataArray[1] = 124;

            if (up)
                dataArray[2] = 127 - speed.Value;
            else if (down)
                dataArray[2] = 127 + speed.Value;
            else if (!down && !up && !shift)
            {
                dataArray[1] = 124;
                dataArray[2] = 127;
            }

            if (shift)
                dataArray[11] = 1;
            else if (!shift)
                dataArray[11] = 0;

            if (Z && speed.Value != 44)
                speed.Value -= 2;
            else if (X && speed.Value != 124)
                speed.Value += 2;

            if (tLeft)
                dataArray[7] = 1;
            else if (!tLeft)
                dataArray[7] = 0;

            if (tRight)
                dataArray[5] = 1;
            else if (!tRight)
                dataArray[5] = 0;

            if (ledPressed)
                dataArray[9] = 1;
            else if (!ledPressed)
                dataArray[9] = 0;

            if (laserPressed)
                dataArray[10] = 1;
            else if (!laserPressed)
                dataArray[10] = 0;

            if (W && servoY.Value != 0)
            {
                servoY.Value += 3;
                dataArray[4] = Math.Abs(servoY.Value);
            }
            else if (S && servoY.Value != -180)
            {
                servoY.Value -= 3;
                dataArray[4] = Math.Abs(servoY.Value);
            }
            if (A && servoX.Value != 180)
            {
                servoX.Value += 3;
                dataArray[3] = servoX.Value;
            }
            else if (D && servoX.Value != 0)
            {
                servoX.Value -= 3;
                dataArray[3] = servoX.Value;
            }

            if (C)
            {
                servoX.Value = 81;
                servoY.Value = -111;
                dataArray[3] = servoX.Value;
                dataArray[4] = Math.Abs(servoY.Value);
            }

            try
            {
                if (serialPort.IsOpen)
                {
                    foreach (int data in dataArray)
                        serialPort.WriteLine(Convert.ToString(data));
                }
                else
                {
                    COM.Image = Properties.Resources.COM_OFF;
                }
            }
            catch (Exception)
            {
                BoxCOM.SelectedIndex = 0;
                COM.Image = Properties.Resources.COM_OFF;
            }
        }
    }
}
