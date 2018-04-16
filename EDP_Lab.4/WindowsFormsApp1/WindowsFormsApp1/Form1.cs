using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        private Graphics graphics;
        private SolidBrush brush;
        private List<Object> objects;
        private int dimensionX;
        private int dimensionY;

        public Form1()
        {
            InitializeComponent();
            DoubleBuffered = true;
            objects = new List<Object>();
            this.MouseWheel += from_MouseWheel;
            dimensionX = 40;
            dimensionY = 40;
        }

        private void from_MouseWheel(object sender, MouseEventArgs e)
        {
            if(e.Delta > 0)
            {
                if(this.timer1.Interval > 1)
                {
                    this.timer1.Interval-=20;
                }
                else
                {
                    MessageBox.Show("It is the max speed.");
                }
            }

            if(e.Delta < 0)
            {
                if(this.timer1.Interval < 41)
                {
                    this.timer1.Interval+=20;
                }
                else
                {
                    MessageBox.Show("It is the min speed.");
                }
            }

            switch(this.timer1.Interval)
            {
                case 1:
                    this.label2.Text = "Speed: High";
                    break;

                case 21:
                    this.label2.Text = "Speed: Medium";
                    break;

                case 41:
                    this.label2.Text = "Speed: Low";
                    break;
            }
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            foreach(var obj in objects)
            {
                e.Graphics.FillEllipse(obj.brush, obj.PosX, obj.PosY, obj.DimensionX, obj.DimensionY);
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            foreach(var obj in objects)
            {
                obj.MoveObj();
                Move_NyanCat();
                Collision(obj);
            }
            Invalidate();
        }

        private void Form1_MouseClick(object sender, MouseEventArgs e)
        {
            int speedX = 2, speedY = 2;
            bool create = true;
            foreach(var obj in objects)
            {
                if(Math.Abs(e.X - obj.PosX) <= obj.DimensionX && Math.Abs(e.Y - obj.PosY) <= obj.DimensionY)
                {
                    create = false;
                    MessageBox.Show("You can not create a ball inside another ball");
                }
            }

            if (e.X + dimensionX >= this.ClientSize.Width || e.Y + dimensionY >= this.ClientSize.Height)
            {
                create = false;
                MessageBox.Show("You can not create a ball out of Form's Area");
            }

            double areaOfObject = 2 * Math.PI * Math.Pow((dimensionX / 2), 2);
            double areaOfForm = this.ClientSize.Width * this.ClientSize.Height;
            if(objects.Count * areaOfObject > areaOfForm / 6)
            {
                create = false;
                MessageBox.Show("The window is too small, in order add more" +
                                "\nobjects make it larger!");                                
            }

            if(create)
            {
                if(Object.count % 4 == 3)
                {
                    speedX = -2;
                }
                if(Object.count % 4 == 2)
                {
                    speedY = -2;
                }
                if (Object.count % 4 == 1)
                {
                    speedX = -2;
                    speedY = -2;
                }

                objects.Add(new Object(e.X, e.Y, speedX, speedY, dimensionX, dimensionY));
            }
        }

        public void Collision(Object obj)
        {
            bool collision = false;

            if(obj.PosX + obj.DimensionX >= this.ClientSize.Width)
            {
                collision = true;
                obj.MoveX = -obj.MoveX;
                obj.ChangeColor();
                System.Media.SystemSounds.Beep.Play();                
            }
            if(obj.PosX <= 0)
            {
                collision = true;
                obj.MoveX = -obj.MoveX;
                obj.ChangeColor();
                System.Media.SystemSounds.Asterisk.Play();
            }

            if(obj.PosY + obj.DimensionY >= this.ClientSize.Height)
            {
                collision = true;
                obj.MoveY = -obj.MoveY;
                obj.ChangeColor();
                this.BackColor = this.BackColor == Color.Blue ? this.BackColor = Color.Green : this.BackColor = Color.Blue;
            }
            if(obj.PosY <= 0)
            {
                collision = true;
                obj.MoveY = -obj.MoveY;
                obj.ChangeColor();
                this.BackColor = this.BackColor == Color.Blue ? this.BackColor = Color.Green : this.BackColor = Color.Blue;
            }

            if (this.pictureBox1.Location.X >= this.ClientSize.Width)
            {
                collision = true;
                this.pictureBox1.Enabled = false;
            }

            if(collision)
            {
                return;
            }
        }

        public void Move_NyanCat()
        {
            this.pictureBox1.Location = new Point(this.pictureBox1.Location.X + 1, this.pictureBox1.Location.Y);
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.B)
            {
                if(this.timer1.Enabled == true)
                {
                    this.timer1.Enabled = false;
                }
                else
                {
                    this.timer1.Enabled = true;
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.timer1.Enabled = true;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.timer1.Enabled = false;
        }
    }
}
