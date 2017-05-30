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
    public partial class ExposureForm : Form
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


        private Adjustments exposure;
        private Bitmap input;


        public ExposureForm()
        {
            InitializeComponent();         
        }


        private void ExposureForm_Load(object sender, EventArgs e)
        {
            exposure = new Adjustments();

            exposureTrackBar.Minimum = -200;
            exposureTrackBar.Maximum = 200;
            exposureTrackBar.Value = 0;
            exposureValue.Text = "0,00";

            gammaTrackBar.Minimum = 1;
            gammaTrackBar.Maximum = 799;
            gammaTrackBar.Value = 400;
            gammaValue.Text = "1,00";
        }


        public void SetInputImage(object sender, ImageProcessingEventArgs e)
        {
            input = e.Image;
        }

     
        private double ComputeGammaValue()
        {
            return gammaTrackBar.Value < 400 ? gammaTrackBar.Value / 400.0 : (gammaTrackBar.Value - 400.0) * 7 / 400 + 1;
        }


        private double ComputeExposureValue()
        {
            return exposureTrackBar.Value / 100.0;
        }


        private void exposureTrackBar_Scroll(object sender, EventArgs e)
        {      
            exposureValue.Text = ComputeExposureValue().ToString();
        }


        private void gammaTrackBar_Scroll(object sender, EventArgs e)
        {
            gammaValue.Text = ComputeGammaValue().ToString();
        }   


        private void exposureValue_TextChanged(object sender, EventArgs e)
        {
            double value;

            if (Synchronization.IsValueValid(exposureValue.Text, -2, 2, out value))
                exposureTrackBar.Value = (int)(value * 100);
        }


        private int ComputeGammaTrackBarValue(double gamma)
        {
            return (int)(gamma < 1 ? gamma * 400 : (gamma - 1) * 400 / 7 + 400);
        } 


        private void gammaValue_TextChanged(object sender, EventArgs e)
        {
            double value;
            if (Synchronization.IsValueValid(gammaValue.Text, 0.0025, 7.99, out value))
                gammaTrackBar.Value = ComputeGammaTrackBarValue(value);      
        }

      
        private void exposureTrackBar_ValueChanged(object sender, EventArgs e)
        {
            Bitmap preview = new Bitmap(input);
            exposure.AdjustExposure(preview, ComputeExposureValue(), ComputeGammaValue());
            OnProcessingCompleted(preview);
        }


        private void gammaTrackBar_ValueChanged(object sender, EventArgs e)
        {
            Bitmap preview = new Bitmap(input);
            exposure.AdjustExposure(preview, ComputeExposureValue(), ComputeGammaValue());
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
