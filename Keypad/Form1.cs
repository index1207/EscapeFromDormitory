namespace Keypad
{
    public partial class Form : System.Windows.Forms.Form
    {
        public string password;
        public Form()
        {
            InitializeComponent();
            password = "";
        }

        private void button_Click(object sender, EventArgs e)
        {
            Button button = (Button)sender;
            password += button.Text;
        }
        private void buttonOk_Click(object sender, EventArgs e)
        {
            if(password == "0613")
            {
                Display.Text = "확인";
                Thread.Sleep(1000);
                Display.Text = "!!탈출 성공!!";

                StreamWriter sw = new StreamWriter(new FileStream("exit.txt", FileMode.Open));
                sw.Write("T");
                sw.Close();

                password = "";
            }
            else
            {
                Display.Text = "다시 입력해주세요.";
                password = "";
            }
        }
    }
}