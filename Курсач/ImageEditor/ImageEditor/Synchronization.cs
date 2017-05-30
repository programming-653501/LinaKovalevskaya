using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;

namespace ImageEditor
{
    class Synchronization
    {
        public static void SynchronizeTrackBar(TrackBar trackBar, TextBox textBox)
        {
            int value;
            if (int.TryParse(textBox.Text, out value) &&
                value >= trackBar.Minimum &&
                value <= trackBar.Maximum)

                trackBar.Value = value;
        }

        public static void SynchronizeTextBox(TextBox textBox, TrackBar trackBar)
        {
            textBox.Text = trackBar.Value.ToString();
        }

        public static void SynchronizePictureBox(PictureBox pictureBox, Bitmap image)
        {
            pictureBox.Height = image.Height;
            pictureBox.Width = image.Width;
        }

        public static bool IsValueValid(string value, double lowerBorder, double upperBorder, out double validated)
        {
            return (double.TryParse(value, out validated) && validated >= lowerBorder && validated <= upperBorder) ? true : false;
        }

        public static bool IsValueValid(string value, int lowerBorder, int upperBorder, out int validated)
        {
            return (int.TryParse(value, out validated) && validated >= lowerBorder && validated <= upperBorder) ? true : false;
        }

        public static int GetLessValue(int x, int y)
        {
            return x < y ? x : y;
        }
    }
}
