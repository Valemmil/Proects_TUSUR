using System.Windows;

namespace TUSUR_Journal.Windows
{
    /// <summary>
    /// Логика взаимодействия для ExampleWindow.xaml
    /// </summary>
    public partial class ExampleWindow : Window
    {
        public ExampleWindow()
        {
            InitializeComponent();
        }

        private void CloseWindow(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
