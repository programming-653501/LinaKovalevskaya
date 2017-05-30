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
    public partial class ColorBalanceForm : Form
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


        Adjustments colorBalance;
        Bitmap input;


        public void SetInputImage(object sender, ImageProcessingEventArgs e)
        {
            input = e.Image;
        }


        public ColorBalanceForm()
        {
            InitializeComponent();
        }


        private void ColorBalanceForm_Load(object sender, EventArgs e)
        {
            colorBalance = new Adjustments();

            redTrackBar.Value = 0;
            redValue.Text = "0";

            greenTrackBar.Value = 0;
            greenValue.Text = "0";

            blueTrackBar.Value = 0;
            blueValue.Text = "0";
        }


        private void redTrackBar_Scroll(object sender, EventArgs e)
        {
            Synchronization.SynchronizeTextBox(redValue, redTrackBar);
        }


        private void greenTrackBar_Scroll(object sender, EventArgs e)
        {
            Synchronization.SynchronizeTextBox(greenValue, greenTrackBar);
        }


        private void blueTrackBar_Scroll(object sender, EventArgs e)
        {
            Synchronization.SynchronizeTextBox(blueValue, blueTrackBar);
        }


        private void redTrackBar_ValueChanged(object sender, EventArgs e)
        {
            Bitmap preview = new Bitmap(input);
            colorBalance.AdjustColorBalance(preview, redTrackBar.Value, greenTrackBar.Value, blueTrackBar.Value);
            OnProcessingCompleted(preview);
        }


        private void greenTrackBar_ValueChanged(object sender, EventArgs e)
        {
            Bitmap preview = new Bitmap(input);
            colorBalance.AdjustColorBalance(preview, redTrackBar.Value, greenTrackBar.Value, blueTrackBar.Value);
            OnProcessingCompleted(preview);
        }


        private void blueTrackBar_ValueChanged(object sender, EventArgs e)
        {
            Bitmap preview = new Bitmap(input);
            colorBalance.AdjustColorBalance(preview, redTrackBar.Value, greenTrackBar.Value, blueTrackBar.Value);
            OnProcessingCompleted(preview);
        }


        private void redValue_TextChanged(object sender, EventArgs e)
        {
            Synchronization.SynchronizeTrackBar(redTrackBar, redValue);
        }


        private void greenValue_TextChanged(object sender, EventArgs e)
        {
            Synchronization.SynchronizeTrackBar(greenTrackBar, greenValue);
        }


        private void blueValue_TextChanged(object sender, EventArgs e)
        {
            Synchronization.SynchronizeTrackBar(blueTrackBar, blueValue);
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
