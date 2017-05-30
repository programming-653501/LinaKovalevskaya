using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;

namespace ImageEditor
{
    class FileOperations
    {
        public class OpenEventArgs
        {
            public OpenEventArgs(Bitmap bitmap)
            {
                Input = bitmap;
            }

            public Bitmap Input { get; }
        }

        public delegate void OpenFileEventHandler(object sender, OpenEventArgs e);

        public event OpenFileEventHandler FileOpened;

        protected virtual void OnFileOpened(Bitmap input)
        {
            FileOpened?.Invoke(this, new OpenEventArgs(input));
        }

        
        public void OpenImageFile()
        {
            Bitmap input = null;
            OpenFileDialog openFileDialog = new OpenFileDialog();

            openFileDialog.InitialDirectory = "D:\\drawing\\";
            openFileDialog.Filter = "Image Files(*.JPG; *.BMP; *.PNG)| *.JPG; *.BMP; *.PNG";
            openFileDialog.CheckFileExists = true;
            openFileDialog.CheckPathExists = true;
            openFileDialog.RestoreDirectory = true;

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    input = new Bitmap(Image.FromFile(openFileDialog.FileName));
                }

                catch (Exception exception)
                {
                    MessageBox.Show("Error: Could not read file from disk. Original error: " + exception.Message);
                }
            }

            OnFileOpened(input);
        }

        public void SaveImageFileAs(Bitmap image)
        {

            SaveFileDialog saveFileDialog = new SaveFileDialog();

            saveFileDialog.Filter = "JPG Image|*.jpg|BMP Image|*.bmp|PNG Image|*.png";
            saveFileDialog.AddExtension = true;
            saveFileDialog.OverwritePrompt = true;
            saveFileDialog.RestoreDirectory = true;

            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    image.Save(saveFileDialog.FileName);
                }
                catch (Exception exception)
                {
                    MessageBox.Show("Error: Could not write file to disk. Original error: " + exception.Message);
                }
            }
        }
    }
}
