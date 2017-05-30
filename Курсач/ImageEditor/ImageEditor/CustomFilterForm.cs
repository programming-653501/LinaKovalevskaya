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
    public partial class CustomFilterForm : Form
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


        private CustomFilter customFilter;
        private Bitmap input;
        private CustomFilterAdjustment adjustment;
        private int maximalIntensity;


        public void SetInputImage(object sender, CustomFilterEventArgs e)
        {         
            input = new Bitmap(e.Input);          
            customFilter = e.Filter;
            adjustment = e.Adjustment;
            maximalIntensity = 2 * Synchronization.GetLessValue(input.Height, input.Width) + 1;
        }


        private void CustomFilterForm_Load(object sender, EventArgs e)
        {
            intensityValue.Text = "1";
        }


        public CustomFilterForm()
        {
            InitializeComponent();
        }

     
        private void intensityValue_TextChanged(object sender, EventArgs e)
        {
            int value;

            if (!Synchronization.IsValueValid(intensityValue.Text, 1, maximalIntensity, out value))
                return;

            if (value == 1)
            {
                OnProcessingCompleted(input);
                return;
            }

            customFilter.SetUp(value);
            Bitmap preview = new Bitmap(input);
            preview = adjustment(preview);
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
