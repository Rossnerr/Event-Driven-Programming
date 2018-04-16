using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsFormsApp1
{
    public class Object
    {
        public static int count = 0;

        public float CenterX { get; set; }
        public float CenterY { get; set; }

        public int Id { get; set; }
        public float DimensionX { get; set; }
        public float DimensionY { get; set; }

        public float PosX { get; set; }
        public float PosY { get; set; }

        public float MoveX { get; set; }
        public float MoveY { get; set; }

        public SolidBrush brush { get; set; }

        public Object(float posX, float posY, float moveX, float moveY, float dimensionX, float dimensionY)
        {
            count++;
            Id = count;
            PosX = posX;
            PosY = posY;

            MoveX = moveX;
            MoveY = moveY;

            DimensionX = dimensionX;
            DimensionY = dimensionY;

            CenterX = PosX + DimensionX / 2;
            CenterY = PosY + DimensionY / 2;
         
            brush = new SolidBrush(Color.Red);
        }

        public void MoveObj()
        {
            PosX += MoveX;
            PosY += MoveY;

            CenterX = PosX + DimensionX / 2;
            CenterY = PosY + DimensionY / 2;
        }


        public void ChangeColor()
        {
            this.brush.Color = this.brush.Color == Color.Red ? this.brush.Color = Color.Black : this.brush.Color = Color.Red;
        }
    }
}