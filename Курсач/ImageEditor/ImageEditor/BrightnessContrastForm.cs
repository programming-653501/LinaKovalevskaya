using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ImageEditor
{
    public partial class BrightnessContrastForm : Form
    {
        public event ImageProcessingEventHandler ProcessingCompleted;


        protected virtual void OnProcessingCompleted(Bitmap processedImage)
        {
            ProcessingCompleted?.Invoke(this, new ImageProcessingEventArgs() { Image = processedImage });
        }


        public event ImageProcessingEventHandler ProcessingApproved;


        protected virtual void OnProcessingApproved()
        {
            ProcessingApproved?.Invoke(this, new ImageProcessingEventArgs());
        }


        public event ImageProcessingEventHandler ProcessingCanceled;


        protected virtual void OnProcessingCanceled()
        {
            ProcessingCanceled?.Invoke(this, new ImageProcessingEventArgs());
        }


        private Adjustments brightnessContast;
        private Bitmap input;


        public BrightnessContrastForm()
        {
            InitializeComponent();
        }


        private void BrightnessContrastForm_Load(object sender, EventArgs e)
        {
            brightnessContast = new Adjustments();

            brightnessTrackBar.Value = 0;
            brightnessValue.Text = "0";

            contrastTrackBar.Value = 0;
            contrastValue.Text = "0";
        }


        public void SetInputImage(object sender, ImageProcessingEventArgs e)
        {
            input = e.Image;
        }


        private void brightnessTrackBar_Scroll(object sender, EventArgs e)
        {
            Synchronization.SynchronizeTextBox(brightnessValue, brightnessTrackBar);
        }


        private void contrastTrackBar_Scroll(object sender, EventArgs e)
        {
            Synchronization.SynchronizeTextBox(contrastValue, contrastTrackBar);
        }


        private void contrastValue_TextChanged(object sender, EventArgs e)
        {
            Synchronization.SynchronizeTrackBar(contrastTrackBar, contrastValue);
        }


        private void brightnessValue_TextChanged(object sender, EventArgs e)
        {
            Synchronization.SynchronizeTrackBar(brightnessTrackBar, brightnessValue);
        }


        private void brightnessTrackBar_ValueChanged(object sender, EventArgs e)
        {
            Bitmap preview = new Bitmap(input);
            brightnessContast.AdjustBrightnessAndContrast(preview, brightnessTrackBar.Value, contrastTrackBar.Value);
            OnProcessingCompleted(preview);
        }


        private void contrastTrackBar_ValueChanged(object sender, EventArgs e)
        {
            Bitmap preview = new Bitmap(input);
            brightnessContast.AdjustBrightnessAndContrast(preview, brightnessTrackBar.Value, contrastTrackBar.Value);
            OnProcessingCompleted(preview);
        }


        private void okButton_Click(object sender, EventArgs e)
        {
            OnProcessingApproved();
            Close();
        }


        private void cancelButton_Click(object sender, EventArgs e)
        {
            OnProcessingCanceled();
            Close();
        }
    }
}
