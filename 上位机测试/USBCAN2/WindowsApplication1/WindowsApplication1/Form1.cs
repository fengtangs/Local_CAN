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

        float[,] old_data = new float[9, 3];//原始数据
        float[,] new_data = new float[9, 3];//新数据
        float[,] old_fire_time = new float[3, 2];//原始数据
        float[,] new_fire_time = new float[3, 2];//新数据
        //这是data下标
        int ColumnIndeydata = 0;
        int ColumnIndexdata = 0;

        //这是firetime下标
        int ColumnIndeytime = 0;
        int ColumnIndextime = 0;


        bool started_ = false;
        UInt32 m_bOpen = 0;
        UInt32 m_devind = 0;
        UInt32 m_canind = 0;

        byte Out = 0;
        DataGridViewColumn column = new DataGridViewColumn();


        const string startText = "启动CAN";
        const string stopText = "复位CAN";


        [StructLayout(LayoutKind.Explicit, Size = 4)]
        struct f32_type
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
            public float f32;

        }

        f32_type[] Temp = new f32_type[8];//
        f32_type Tempf;

        public Form1()
        {
            InitializeComponent();

        }
        private Button btn = new Button();
        private void Form1_Load(object sender, EventArgs e)
        {


            started_ = false;
            EnableSet();
        }

       //listview2,3
         public void InitList()
        {
            ImageList imglist2 = new ImageList();
            imglist2.ImageSize = new Size(1, 20);
            listView2.SmallImageList = imglist2;
            listView2.View = View.Details;
            ImageList imglist3 = new ImageList();
            imglist3.ImageSize = new Size(1, 20);
            listView3.SmallImageList = imglist3;
            listView3.View = View.Details;

 

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
                A3.Enabled = false;
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
                A3.Enabled = true;
            }
            bool opened = m_bOpen == 1;
            buttonConnect.Text = opened ? "断开" : "连接";
            timer_rec.Enabled = opened;
            EnableSet();

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

        }



        private void timer_rec_Tick(object sender, EventArgs e)
        {
            Control[] c = new Control[1];
            UInt32 res = new UInt32();
            res = Device.VCI_GetReceiveNum(4, 0, 0);
            if (res == 0)
                return;
            UInt32 con_maxlen = 50;
            IntPtr pt = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(VCI_CAN_OBJ)) * (Int32)con_maxlen);
            res = Device.VCI_Receive(4, 0, 0, pt, con_maxlen, 100);
            ////////////////////////////////////////////////////////

            for (UInt32 i = 0; i < res; i++)
            {
                VCI_CAN_OBJ obj = (VCI_CAN_OBJ)Marshal.PtrToStructure((IntPtr)((UInt32)pt + i * Marshal.SizeOf(typeof(VCI_CAN_OBJ))), typeof(VCI_CAN_OBJ));
                if (obj.RemoteFlag == 0)
                {
                    if ((Int32)obj.ID == 5)//温度
                    {
                        byte len = (byte)(obj.DataLen % 9);
                        if (len == 5)
                        {
                            Temp[obj.Data[0]].b0 = obj.Data[1];
                            Temp[obj.Data[0]].b1 = obj.Data[2];
                            Temp[obj.Data[0]].b2 = obj.Data[3];
                            Temp[obj.Data[0]].b3 = obj.Data[4];
                            string LabelName = "Temp" + obj.Data[0].ToString();
                            c = this.Controls.Find(LabelName, true);
                            if (c.Length > 0)
                            {
                                Label Lableb = (Label)c[0];
                                Lableb.Text = Temp[obj.Data[0]].f32.ToString("f2") + "度";
                            }
                        };
                    };
                    if ((Int32)obj.ID == 7)//温度
                    {
                        byte len = (byte)(obj.DataLen % 9);
                        if (len == 5)
                        {

                            Tempf.b0 = obj.Data[1];
                            Tempf.b1 = obj.Data[2];
                            Tempf.b2 = obj.Data[3];
                            Tempf.b3 = obj.Data[4];
                            int y = obj.Data[0]%9;
                            int x = obj.Data[0]/9+1;
                            listView1.Items[y].SubItems[x].Text = Tempf.f32.ToString("f3");
                        };
                    };
                    if ((Int32)obj.ID == 8)//温度
                    {
                        byte len = (byte)(obj.DataLen % 9);
                        if (len == 2)
                        {
                           if(obj.Data[1]==0)
                           {
                               label9.Text = "0：载气断开";
                           }
                           else
                           {
                               label9.Text = "1：载气正常";
                               

                           }
                        };
                    };
 
                }
            }
            Marshal.FreeHGlobal(pt);
        }

         private void Send_Pakage(uint id,byte[] Buf)
         {
             int num = 1;
             VCI_CAN_OBJ[] sendob = new VCI_CAN_OBJ[num];//sendobj.Init();
             sendob[0].SendType = (byte)0x0;
             sendob[0].RemoteFlag = (byte)0x0;
             sendob[0].ExternFlag = (byte)0x0;
             sendob[0].TimeFlag = (byte)0x0;
             sendob[0].ID = id;
             //sendob[0].ID = 0x00000008;
             sendob[0].DataLen = (byte)0x2;
             sendob[0].Data = Buf;
             uint res = Device.VCI_Transmit(4, 0, 0, sendob, (uint)num);

         }

        private void A3_Click(object sender, EventArgs e)
        {
            Control[] c = new Control[1];
            byte[] Buf = new byte[8];
            Buf[0] = (byte)0x02;
            Buf[1] = 0x01;
            Send_Pakage(0x00000008, Buf);
            for (int i = 0;i < 8; i++)
            {
                string LabelName = "Temp" + i.ToString();
                c = this.Controls.Find(LabelName, true);
                if (c.Length > 0)
                {
                    Temp[i].f32 = 0;
                    Label Lableb = (Label)c[0];
                    Lableb.Text = Temp[i].f32.ToString("f2") + "度";
                }
            };


        }

        private void button1_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {

        }

        private void groupBox6_Enter(object sender, EventArgs e)
        {

        }

        private void label9_Click(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {
             byte[] Buf= new byte[8];
             Buf[0] = (byte)0x00;
             Buf[1] = 0x00;
             Send_Pakage(0x00000009,Buf);

        }

        private void button3_Click(object sender, EventArgs e)
        {
            byte[] Buf = new byte[8];
            Buf[0] = (byte)0x00;
            Buf[1] = 0x01;
            Send_Pakage(0x00000009, Buf);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            byte[] Buf = new byte[8];
            Buf[0] = (byte)0x00;
            Buf[1] = 0x02;
            Send_Pakage(0x00000009, Buf);
        }

        private void checkBox16_CheckedChanged(object sender, EventArgs e)
        {
            byte[] Buf = new byte[8];
            if (checkBox16.Checked)
            {
                Out = (byte)(1 | Out);
            }
            else
            {
                Out = (byte)((~1) & Out);
            };
            Buf[0] = (byte)0x07;
            Buf[1] = Out;
            Send_Pakage(0x00000009, Buf);

        }

        private void checkBox15_CheckedChanged(object sender, EventArgs e)
        {
            byte[] Buf = new byte[8];
            if (checkBox15.Checked)
            {
                Out = (byte)(2 | Out);
            }
            else
            {
                Out = (byte)((~2) & Out);
            };
            Buf[0] = (byte)0x07;
            Buf[1] = Out;
            Send_Pakage(0x00000009, Buf);
        }

        private void checkBox14_CheckedChanged(object sender, EventArgs e)
        {
            byte[] Buf = new byte[8];
            if (checkBox14.Checked)
            {
                Out = (byte)(4 | Out);
            }
            else
            {
                Out = (byte)((~4) & Out);
            };
            Buf[0] = (byte)0x07;
            Buf[1] = Out;
            Send_Pakage(0x00000009, Buf);
        }

        private void checkBox13_CheckedChanged(object sender, EventArgs e)
        {
            byte[] Buf = new byte[8];
            if (checkBox13.Checked)
            {
                Out = (byte)(8 | Out);
            }
            else
            {
                Out = (byte)((~8) & Out);
            };
            Buf[0] = (byte)0x07;
            Buf[1] = Out;
            Send_Pakage(0x00000009, Buf);
        }

        private void checkBox12_CheckedChanged(object sender, EventArgs e)
        {
            byte[] Buf = new byte[8];
            if (checkBox12.Checked)
            {
                Out = (byte)(0x10 | Out);
            }
            else
            {
                Out = (byte)((~0x10) & Out);
            };
            Buf[0] = (byte)0x07;
            Buf[1] = Out;
            Send_Pakage(0x00000009, Buf);
        }

        private void checkBox11_CheckedChanged(object sender, EventArgs e)
        {
            byte[] Buf = new byte[8];
            if (checkBox11.Checked)
            {
                Out = (byte)(0x20 | Out);
            }
            else
            {
                Out = (byte)((~0x20) & Out);
            };
            Buf[0] = (byte)0x07;
            Buf[1] = Out;
            Send_Pakage(0x00000009, Buf);
        }

        private void checkBox10_CheckedChanged(object sender, EventArgs e)
        {
            byte[] Buf = new byte[8];
            if (checkBox10.Checked)
            {
                Out = (byte)(0x40 | Out);
            }
            else
            {
                Out = (byte)((~0x40) & Out);
            };
            Buf[0] = (byte)0x07;
            Buf[1] = Out;
            Send_Pakage(0x00000009, Buf);
        }

        private void checkBox9_CheckedChanged(object sender, EventArgs e)
        {
            byte[] Buf = new byte[8];
            if (checkBox9.Checked)
            {
                Out = (byte)(0x80 | Out);
            }
            else
            {
                Out = (byte)((~0x80) & Out);
            };
            Buf[0] = (byte)0x07;
            Buf[1] = Out;
            Send_Pakage(0x00000009, Buf);
        }


        [DllImport("user32")]
        public static extern int GetScrollPos(int hwnd, int nBar);
        private TextBox txtInput;

        private void listView2_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            try
            {
                ListViewItem item = this.listView2.GetItemAt(e.X, e.Y);
                //找到文本框
                Rectangle rect = item.GetBounds(ItemBoundsPortion.Entire);
                int StartX = rect.Left; //获取文本框位置的X坐标
                int StartY = rect.Y;
                ColumnIndeydata = this.listView2.Items[listView2.SelectedIndices[0]].Index;
                ColumnIndexdata = 0;    //文本框的索引
                //获取列的索引
                //得到滑块的位置
                int pos = GetScrollPos(this.listView2.Handle.ToInt32(), 0);
                foreach (ColumnHeader Column in listView2.Columns)
                {
                    if (e.X + pos >= StartX + Column.Width)
                    {
                        StartX += Column.Width;
                        ColumnIndexdata += 1;
                    }
                }
                if (ColumnIndexdata < 1)//第一列为序号，不修改。如果双击为第一列则不可以进入修改
                {
                    return;
                }

                this.txtInput = new TextBox();

                this.txtInput.Parent = this.listView2;

                //begin edit
                if (item != null)
                {
                    rect.X = StartX;
                    rect.Width = this.listView2.Columns[ColumnIndexdata].Width; //得到长度和ListView的列的长度相同                    
                    this.txtInput.Bounds = rect;
                    this.txtInput.Multiline = true;
                    //显示文本框
                    this.txtInput.Text = item.SubItems[ColumnIndexdata].Text;
                    // 获取上次内容
                    old_data[ColumnIndeydata, ColumnIndexdata - 1] = (float)Convert.ToSingle(item.SubItems[ColumnIndexdata].Text);
                    this.txtInput.Tag = item.SubItems[ColumnIndexdata];
                    this.txtInput.KeyPress += new KeyPressEventHandler(txtInput_KeyPress);
                    this.txtInput.Focus();
                }
            }
            catch (Exception ex)
            {
            }
        }

        //添加回车保存内容
        private void txtInput_KeyPress(object sender, KeyPressEventArgs e)
        {
            try
            {

                TextBox tb = sender as TextBox;
                if (e.KeyChar != 8 && !Char.IsDigit(e.KeyChar) && e.KeyChar != 0x2E)//如果键入的不是回退并且不是数字还不是‘.'
                {
                    e.Handled = true;
                };
                if (e.KeyChar == '.')   //允许输入回退键
                {
                    if (tb.Text == "")
                    {
                        tb.Text = "0.";
                        tb.Select(tb.Text.Length, 0);
                        e.Handled = true;
                    }
                    else if (tb.Text.Contains("."))
                    {
                        e.Handled = true;
                    }
                    else
                    {
                        e.Handled = false;
                    };
                };
                if (e.KeyChar == 0x0d)
                {
                    ListViewItem.ListViewSubItem lvst = (ListViewItem.ListViewSubItem)this.txtInput.Tag;
                    new_data[ColumnIndeydata, ColumnIndexdata - 1] = (float)Convert.ToSingle(tb.Text);
                    lvst.Text = Convert.ToString(new_data[ColumnIndeydata, ColumnIndexdata - 1]);
                    this.txtInput.Dispose();
                    e.Handled = true;
                }


            }
            catch (Exception ex)
            {
            }
        }


        //添加事件SelectedIndexChanged，释放文本框内容
        private void listView2_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                if (this.txtInput != null)
                {
                    if (this.txtInput.Text.Length > 0)
                    {
                        ListViewItem.ListViewSubItem lvst = (ListViewItem.ListViewSubItem)this.txtInput.Tag;
                        new_data[ColumnIndeydata, ColumnIndexdata - 1] = (float)Convert.ToSingle(this.txtInput.Text);
                        lvst.Text = Convert.ToString(new_data[ColumnIndeydata, ColumnIndexdata - 1]);
                    }

                    this.txtInput.Dispose();
                }
            }
            catch (Exception ex)
            {
            }
        }

        //添加事件，鼠标单击MouseClick，将文本框内容显示在listview2

        private void listView2_MouseClick(object sender, MouseEventArgs e)
        {
            try
            {
                if (this.txtInput != null)
                {
                    if (this.txtInput.Text.Length > 0)
                    {
                        ListViewItem.ListViewSubItem lvst = (ListViewItem.ListViewSubItem)this.txtInput.Tag;
                        new_data[ColumnIndeydata, ColumnIndexdata - 1] = (float)Convert.ToSingle(this.txtInput.Text);
                        lvst.Text = Convert.ToString(new_data[ColumnIndeydata, ColumnIndexdata - 1]);
                    }

                    this.txtInput.Dispose();
                }
            }
            catch (Exception ex)
            {
            }
        }

        private void listView3_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            try
            {
                ListViewItem item = this.listView3.GetItemAt(e.X, e.Y);
                //找到文本框
                Rectangle rect = item.GetBounds(ItemBoundsPortion.Entire);
                int StartX = rect.Left; //获取文本框位置的X坐标
                int StartY = rect.Y;
                ColumnIndeytime = this.listView3.Items[listView3.SelectedIndices[0]].Index;
                ColumnIndextime = 0;    //文本框的索引
                //获取列的索引
                //得到滑块的位置
                int pos = GetScrollPos(this.listView3.Handle.ToInt32(), 0);
                foreach (ColumnHeader Column in listView3.Columns)
                {
                    if (e.X + pos >= StartX + Column.Width)
                    {
                        StartX += Column.Width;
                        ColumnIndextime += 1;
                    }
                }
                if (ColumnIndextime < 1)//第一列为序号，不修改。如果双击为第一列则不可以进入修改
                {
                    return;
                }

                this.txtInput = new TextBox();

                this.txtInput.Parent = this.listView3;

                //begin edit
                if (item != null)
                {
                    rect.X = StartX;
                    rect.Width = this.listView3.Columns[ColumnIndextime].Width; //得到长度和ListView的列的长度相同                    
                    this.txtInput.Bounds = rect;
                    this.txtInput.Multiline = true;
                    //显示文本框
                    this.txtInput.Text = item.SubItems[ColumnIndextime].Text;
                    // 获取上次内容
                    old_fire_time[ColumnIndeytime, ColumnIndextime - 1] = (float)Convert.ToSingle(item.SubItems[ColumnIndextime].Text);
                    this.txtInput.Tag = item.SubItems[ColumnIndextime];
                    this.txtInput.KeyPress += new KeyPressEventHandler(txtInput_3KeyPress);
                    this.txtInput.Focus();
                }
            }
            catch (Exception ex)
            {
            }
        }

        //添加回车保存内容
        private void txtInput_3KeyPress(object sender, KeyPressEventArgs e)
        {
            try
            {

                TextBox tb = sender as TextBox;
                if (e.KeyChar != 8 && !Char.IsDigit(e.KeyChar) && e.KeyChar != 0x2E)//如果键入的不是回退并且不是数字还不是‘.'
                {
                    e.Handled = true;
                };
                if (e.KeyChar == '.')   //允许输入回退键
                {
                    if (tb.Text == "")
                    {
                        tb.Text = "0.";
                        tb.Select(tb.Text.Length, 0);
                        e.Handled = true;
                    }
                    else if (tb.Text.Contains("."))
                    {
                        e.Handled = true;
                    }
                    else
                    {
                        e.Handled = false;
                    };
                };
                if (e.KeyChar == 0x0d)
                {
                    ListViewItem.ListViewSubItem lvst = (ListViewItem.ListViewSubItem)this.txtInput.Tag;
                    new_fire_time[ColumnIndeytime, ColumnIndextime - 1] = (float)Convert.ToSingle(tb.Text);
                    lvst.Text = Convert.ToString(new_fire_time[ColumnIndeytime, ColumnIndextime - 1]);
                    this.txtInput.Dispose();
                    e.Handled = true;
                }


            }
            catch (Exception ex)
            {
            }
        }


        //添加事件SelectedIndexChanged，释放文本框内容
        private void listView3_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                if (this.txtInput != null)
                {
                    if (this.txtInput.Text.Length > 0)
                    {
                        ListViewItem.ListViewSubItem lvst = (ListViewItem.ListViewSubItem)this.txtInput.Tag;
                        new_fire_time[ColumnIndeytime, ColumnIndextime - 1] = (float)Convert.ToSingle(this.txtInput.Text);
                        lvst.Text = Convert.ToString(new_fire_time[ColumnIndeytime, ColumnIndextime - 1]);
                    }

                    this.txtInput.Dispose();
                }
            }
            catch (Exception ex)
            {
            }
        }

        //添加事件，鼠标单击MouseClick，将文本框内容显示在listview3

        private void listView3_MouseClick(object sender, MouseEventArgs e)
        {
            try
            {
                if (this.txtInput != null)
                {
                    if (this.txtInput.Text.Length > 0)
                    {
                        ListViewItem.ListViewSubItem lvst = (ListViewItem.ListViewSubItem)this.txtInput.Tag;
                        new_fire_time[ColumnIndeytime, ColumnIndextime - 1] = (float)Convert.ToSingle(this.txtInput.Text);
                        lvst.Text = Convert.ToString(new_fire_time[ColumnIndeytime, ColumnIndextime - 1]);
                    }

                    this.txtInput.Dispose();
                }
            }
            catch (Exception ex)
            {
            }
        }


 


    }
}