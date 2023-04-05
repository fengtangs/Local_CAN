using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using ControlCAN;

namespace WindowsApplication1
{
    
    public partial class Form1 : Form
    {
        static UInt32 m_devtype = 4;//USBCAN2

        bool started_ = false;
        UInt32 m_bOpen = 0;
        UInt32 m_devind = 0;
        UInt32 m_canind = 0;
        const string startText = "启动CAN";
        const string stopText = "复位CAN";

        [StructLayout(LayoutKind.Explicit, Size = 4)]
        struct w32_type
        {
            [FieldOffset(0)]
            public byte b0;
            [FieldOffset(1)]
            public byte b1;
            [FieldOffset(2)]
            public byte b2;
            [FieldOffset(3)]
            public byte b3;
            [FieldOffset(0)]
            public int w32;

        }

        w32_type w32_1;//滤波后数据
        w32_type w32_2;//滤波前数据

        public Queue<double> FIFO1;//滤波后数据
        public Queue<double> FIFO2;

        VCI_CAN_OBJ[] m_recobj = new VCI_CAN_OBJ[50];

        UInt32[] m_arrdevtype = new UInt32[20];

        public Form1()
        {
            InitializeComponent();
            FIFO1 = new Queue<double>(100);
            FIFO2 = new Queue<double>(100);

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            comboBox_SendType.SelectedIndex = 0;
            comboBox_FrameFormat.SelectedIndex = 0;
            comboBox_FrameType.SelectedIndex = 0;
            textBox_ID.Text = "0000001";
            textBox_Data.Text = "02 a0 00 ";


            started_ = false;
            button_StartCAN.Enabled = false;
            button_StartCAN.Text = startText;

            EnableSet();
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (m_bOpen == 1)
            {
                Device.VCI_CloseDevice(4, 0);
            }
        }

        private void EnableSet()
        {
            bool opened = m_bOpen == 1;
            int index = 0;
            uint type = 4;
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            int index =0;
            uint type = 4;
            if (m_bOpen == 1)
            {
                Device.VCI_CloseDevice(m_devtype, m_devind);
                m_bOpen = 0;
            }
            else
            {

                if (Device.VCI_OpenDevice(m_devtype, m_devind,0) == 0)
                {
                    MessageBox.Show("打开设备失败,请检查设备类型和设备索引号是否正确", "错误",
                            MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    return;
                }

                VCI_INIT_CONFIG config = new VCI_INIT_CONFIG();
                    config.AccCode = 0x0;
                    config.AccMask = 0xFFFFFFFF;
                    config.Timing0 = 0x0;
                    config.Timing1 = 0x14;
                    config.Filter = 0;
                    config.Mode = 0;
                UInt32 ret = Device.VCI_InitCAN(4, 0, 0, ref config);
                if (ret != 1)
                {
                    MessageBox.Show("InitCAN失败", "错误",
                            MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    return;
                }
                m_bOpen = 1;
            }
            bool opened = m_bOpen == 1;
            buttonConnect.Text = opened ? "断开" : "连接";
            button_StartCAN.Text = startText;
            button_StartCAN.Enabled = opened;
            timer_rec.Enabled = opened;

            EnableSet();
        }



        [StructLayout(LayoutKind.Sequential)]
        private struct SystemTime
        {
            public ushort year;
            public ushort month;
            public ushort dayOfWeek;
            public ushort day;
            public ushort hour;
            public ushort minute;
            public ushort second;
            public ushort milliseconds;
        };

        const string cfgFile = "candtu.ini";
        private class IM28X_TSEG2_TSEG1_SJW
        {
            public byte tSeg2;
            public byte tSeg1Min;
            public byte tSeg1Max;
            public byte rSjwMin;
            public byte rSjwMax;
            public IM28X_TSEG2_TSEG1_SJW(byte seg2, byte seg1min, byte seg1max, byte sjwmin, byte sjwmax)
            {
                tSeg2 = seg2;
                tSeg1Min = seg1min;
                tSeg1Max = seg1max;
                rSjwMin = sjwmin;
                rSjwMax = sjwmax;
            }
        };

        IM28X_TSEG2_TSEG1_SJW[] im28xTseg2Tseg1SjwTable =
        {
            new IM28X_TSEG2_TSEG1_SJW(2, 5, 10, 1, 2),
            new IM28X_TSEG2_TSEG1_SJW(3, 4, 11, 1, 3),
            new IM28X_TSEG2_TSEG1_SJW(4, 5, 12, 1, 4),
            new IM28X_TSEG2_TSEG1_SJW(5, 6, 13, 1, 4),
            new IM28X_TSEG2_TSEG1_SJW(6, 7, 14, 1, 4),
            new IM28X_TSEG2_TSEG1_SJW(7, 8, 15, 1, 4),
            new IM28X_TSEG2_TSEG1_SJW(8, 9, 16, 1, 4)
        };


        private void timer_rec_Tick(object sender, EventArgs e)
        {
            UInt32 res = new UInt32();
            res = Device.VCI_GetReceiveNum(4, 0, 0);
            if (res == 0)
                return;

            /////////////////////////////////////
            UInt32 con_maxlen = 50;
            IntPtr pt = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(VCI_CAN_OBJ)) * (Int32)con_maxlen);




            res = Device.VCI_Receive(4, 0, 0, pt, con_maxlen, 100);
            ////////////////////////////////////////////////////////

            String str = "";
            for (UInt32 i = 0; i < res; i++)
            {
                VCI_CAN_OBJ obj = (VCI_CAN_OBJ)Marshal.PtrToStructure((IntPtr)((UInt32)pt + i * Marshal.SizeOf(typeof(VCI_CAN_OBJ))), typeof(VCI_CAN_OBJ));

                str = "Re_Da:";
                str += "  ID:0x" + System.Convert.ToString((Int32)obj.ID, 16);
                str += "  帧格式:";
                if (obj.RemoteFlag == 0)
                    str += "数据帧 ";
                else
                    str += "远程帧 ";
                if (obj.ExternFlag == 0)
                    str += "标准帧 ";
                else
                    str += "扩展帧 ";

                //////////////////////////////////////////
                if (obj.RemoteFlag == 0)
                {
                    if ((Int32)obj.ID == 1)//滤波
                    {


                        str += "数据:";
                        byte len = (byte)(obj.DataLen % 9);
                        byte j = 0;
                        if (j++ < len)
                        {
                            str += " " + System.Convert.ToString(obj.Data[0], 16);
                        }
                        if (j++ < len)
                        {
                            str += " " + System.Convert.ToString(obj.Data[1], 16);
                            w32_1.b0 = obj.Data[1];
                        }
                        if (j++ < len)
                        {
                            str += " " + System.Convert.ToString(obj.Data[2], 16);
                            w32_1.b1 = obj.Data[2];
                        }
                        if (j++ < len)
                        {
                            str += " " + System.Convert.ToString(obj.Data[3], 16);
                            w32_1.b2 = obj.Data[3];
                        }
                        if (j++ < len)
                        {
                            str += " " + System.Convert.ToString(obj.Data[4], 16);
                            w32_1.b3 = obj.Data[4];
                        }
                        if (j++ < len)
                        {
                            str += " " + System.Convert.ToString(obj.Data[5], 16);
                        }
                        if (j++ < len)
                        {
                            str += " " + System.Convert.ToString(obj.Data[6], 16);
                        }
                        if (j++ < len)
                        {
                            str += " " + System.Convert.ToString(obj.Data[7], 16);
                        }
                        FIFO1.Enqueue(w32_1.w32);

                    }
                    else
                    {

                        str += "数据:";
                        byte len = (byte)(obj.DataLen % 9);
                        byte j = 0;
                        if (j++ < len)
                        {
                            str += " " + System.Convert.ToString(obj.Data[0], 16);
                        }
                        if (j++ < len)
                        {
                            str += " " + System.Convert.ToString(obj.Data[1], 16);
                            w32_2.b0 = obj.Data[1];
                        }
                        if (j++ < len)
                        {
                            str += " " + System.Convert.ToString(obj.Data[2], 16);
                            w32_2.b1 = obj.Data[2];
                        }
                        if (j++ < len)
                        {
                            str += " " + System.Convert.ToString(obj.Data[3], 16);
                            w32_2.b2 = obj.Data[3];
                        }
                        if (j++ < len)
                        {
                            str += " " + System.Convert.ToString(obj.Data[4], 16);
                            w32_2.b3 = obj.Data[4];
                        }
                        if (j++ < len)
                        {
                            str += " " + System.Convert.ToString(obj.Data[5], 16);
                        }
                        if (j++ < len)
                        {
                            str += " " + System.Convert.ToString(obj.Data[6], 16);
                        }
                        if (j++ < len)
                        {
                            str += " " + System.Convert.ToString(obj.Data[7], 16);
                        }
                        FIFO2.Enqueue(w32_2.w32);
                    }
                  
                       

                }
              //  listBox_Info.Items.Add(str);
              //  listBox_Info.SelectedIndex = listBox_Info.Items.Count - 1;



            }
            Marshal.FreeHGlobal(pt);
        }


        private void button_StartCAN_Click(object sender, EventArgs e)
        {
            if (m_bOpen == 0)
                return;
            if (started_)
            {
                Device.VCI_ResetCAN(4, 0, 0);
            }
            else
            {
                UInt32 ret = Device.VCI_StartCAN(4, 0, 0);
                if (ret != 1)
                {
                    MessageBox.Show("StartCAN失败", "错误",
                            MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                }
            }
            started_ = !started_;
            button_StartCAN.Text = started_ ? stopText : startText;
        }

        private void button_StopCAN_Click(object sender, EventArgs e)
        {
            if (m_bOpen == 0)
                return;
            Device.VCI_ResetCAN(4, 0, 0);
            chart1.Series[0].Points.Clear();
            chart1.Series[1].Points.Clear();

        }

        private void button_Send_Click(object sender, EventArgs e)
        {
            if (m_bOpen == 0)
                return;
            send_data();

        }
        private void send_data()
        {
            int num = 1;
            VCI_CAN_OBJ[] sendobj = new VCI_CAN_OBJ[num];//sendobj.Init();
            for (int j = 0; j < sendobj.Length; j++)
            {
                sendobj[j].SendType = (byte)comboBox_SendType.SelectedIndex;
                sendobj[j].RemoteFlag = (byte)comboBox_FrameFormat.SelectedIndex;
                sendobj[j].ExternFlag = (byte)comboBox_FrameType.SelectedIndex;
                sendobj[j].ID = System.Convert.ToUInt32("0x" + textBox_ID.Text, 16);
                int len = (textBox_Data.Text.Length + 1) / 3;
                sendobj[j].DataLen = System.Convert.ToByte(len);
                String strdata = textBox_Data.Text;
                int i = -1;
                sendobj[j].Data = new byte[8];
                if (i++ < len - 1)
                    sendobj[j].Data[0] = System.Convert.ToByte("0x" + strdata.Substring(i * 3, 2), 16);

                if (i++ < len - 1)
                    sendobj[j].Data[1] = System.Convert.ToByte("0x" + strdata.Substring(i * 3, 2), 16);

                if (i++ < len - 1)
                    sendobj[j].Data[2] = System.Convert.ToByte("0x" + strdata.Substring(i * 3, 2), 16);

                if (i++ < len - 1)
                    sendobj[j].Data[3] = System.Convert.ToByte("0x" + strdata.Substring(i * 3, 2), 16);

                if (i++ < len - 1)
                    sendobj[j].Data[4] = System.Convert.ToByte("0x" + strdata.Substring(i * 3, 2), 16);

                if (i++ < len - 1)
                    sendobj[j].Data[5] = System.Convert.ToByte("0x" + strdata.Substring(i * 3, 2), 16);

                if (i++ < len - 1)
                    sendobj[j].Data[6] = System.Convert.ToByte("0x" + strdata.Substring(i * 3, 2), 16);

                if (i++ < len - 1)
                    sendobj[j].Data[7] = System.Convert.ToByte("0x" + strdata.Substring(i * 3, 2), 16);
                listBox_Info.Items.Add(strdata);
                listBox_Info.SelectedIndex = listBox_Info.Items.Count - 1;
            }

            uint res = Device.VCI_Transmit(4, 0, 0, sendobj, (uint)num);
            if (res == 0)
            {
                MessageBox.Show("发送失败", "错误", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        
        
        }
        private void button1_Click(object sender, EventArgs e)
        {
            chart1.Series[0].Points.Clear();
            chart1.Series[1].Points.Clear();
            listBox_Info.Items.Clear();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (m_bOpen == 1&&button_StartCAN.Text=="复位CAN")
            {
                if(FIFO1.Count!=0)
                {
                
                   double  point = (double)(2500.0 / 0x800000) * FIFO1.Dequeue();//滤波后
                    chart1.Series[1].Points.AddY(point);
                    label1.Text = Convert.ToString(point) + "mv";
                }
                if (FIFO2.Count != 0)
                {
                    double point = (double)(2500.0 / 0x800000) * FIFO2.Dequeue();//滤波前
                    chart1.Series[0].Points.AddY(point);
                    label15.Text = Convert.ToString(point) + "mv";
                }

            
            }

        }


        private void label15_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void chart1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void A0_Click(object sender, EventArgs e)
        {
            int num = 1;
            VCI_CAN_OBJ[] sendob = new VCI_CAN_OBJ[num];//sendobj.Init();
            sendob[0].SendType = (byte)0x0;
            sendob[0].RemoteFlag = (byte)0x0;
            sendob[0].ExternFlag = (byte)0x0;
            sendob[0].TimeFlag = (byte)0x0;
            sendob[0].ID = 0x00000001;
            sendob[0].DataLen = (byte)0x3;
            sendob[0].Data = new byte[8];
            sendob[0].Data[0] = (byte)0x02;
            sendob[0].Data[1] = 0xA0;
            sendob[0].Data[2] = (byte)0x00;
            listBox_Info.Items.Add("档位1");
            listBox_Info.SelectedIndex = listBox_Info.Items.Count - 1;
            uint res = Device.VCI_Transmit(4, 0, 0, sendob, (uint)num);
            if (res == 0)
            {
                MessageBox.Show("发送失败", "错误", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }

        private void A1_Click(object sender, EventArgs e)
        {
            int num = 1;
            VCI_CAN_OBJ[] sendob = new VCI_CAN_OBJ[num];//sendobj.Init();
            sendob[0].SendType = (byte)0x0;
            sendob[0].RemoteFlag = (byte)0x0;
            sendob[0].ExternFlag = (byte)0x0;
            sendob[0].TimeFlag = (byte)0x0;
            sendob[0].ID = 0x00000001;
            sendob[0].DataLen = (byte)0x3;
            sendob[0].Data = new byte[8];
            sendob[0].Data[0] = (byte)0x02;
            sendob[0].Data[1] = 0xA1;
            sendob[0].Data[2] = (byte)0x00;
            listBox_Info.Items.Add("档位2");
            listBox_Info.SelectedIndex = listBox_Info.Items.Count - 1;
            uint res = Device.VCI_Transmit(4, 0, 0, sendob, (uint)num);
            if (res == 0)
            {
                MessageBox.Show("发送失败", "错误", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }

        private void A2_Click(object sender, EventArgs e)
        {
            int num = 1;
            VCI_CAN_OBJ[] sendob = new VCI_CAN_OBJ[num];//sendobj.Init();
            sendob[0].SendType = (byte)0x0;
            sendob[0].RemoteFlag = (byte)0x0;
            sendob[0].ExternFlag = (byte)0x0;
            sendob[0].TimeFlag = (byte)0x0;
            sendob[0].ID = 0x00000001;
            sendob[0].DataLen = (byte)0x3;
            sendob[0].Data = new byte[8];
            sendob[0].Data[0] = (byte)0x02;
            sendob[0].Data[1] = 0xA2;
            sendob[0].Data[2] = (byte)0x00;
            listBox_Info.Items.Add("档位3");
            listBox_Info.SelectedIndex = listBox_Info.Items.Count - 1;
            uint res = Device.VCI_Transmit(4, 0, 0, sendob, (uint)num);
            if (res == 0)
            {
                MessageBox.Show("发送失败", "错误", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }

        private void A3_Click(object sender, EventArgs e)
        {
            int num = 1;
            VCI_CAN_OBJ[] sendob = new VCI_CAN_OBJ[num];//sendobj.Init();
            sendob[0].SendType = (byte)0x0;
            sendob[0].RemoteFlag = (byte)0x0;
            sendob[0].ExternFlag = (byte)0x0;
            sendob[0].TimeFlag = (byte)0x0;
            sendob[0].ID = 0x00000001;
            sendob[0].DataLen = (byte)0x3;
            sendob[0].Data = new byte[8];
            sendob[0].Data[0] = (byte)0x02;
            sendob[0].Data[1] = 0xA3;
            sendob[0].Data[2] = (byte)0x00;
            listBox_Info.Items.Add("档位3");
            listBox_Info.SelectedIndex = listBox_Info.Items.Count - 1;
            uint res = Device.VCI_Transmit(4, 0, 0, sendob, (uint)num);
            if (res == 0)
            {
                MessageBox.Show("发送失败", "错误", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }
    }
}