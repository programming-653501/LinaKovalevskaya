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
    public partial class ThresholdForm : Form
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


        private Adjustments threshold;
        private Bitmap input;


        public ThresholdForm()
        {
            InitializeComponent();
        }


        private void ThresholdForm_Load(object sender, EventArgs e)
        {
            threshold = new Adjustments();

            thresholdTrackBar.Value = 128;
            thresholdValue.Text = "128";
        }


        public void SetInputImage(object sender, ImageProcessingEventArgs e)
        {
            input = e.Image;
        }

        
        private void thresholdValue_TextChanged(object sender, EventArgs e)
        {
            Synchronization.SynchronizeTrackBar(thresholdTrackBar, thresholdValue);
        }


        private void thresholdTrackBar_Scroll(object sender, EventArgs e)
        {
            Synchronization.SynchronizeTextBox(thresholdValue, thresholdTrackBar);
        }


        private void thresholdTrackBar_ValueChanged(object sender, EventArgs e)
        {
            Bitmap preview = new Bitmap(input);
            threshold.Threshold(preview, thresholdTrackBar.Value);
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
