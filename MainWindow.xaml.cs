using System;
using System.IO;
using System.Windows;
using System.Windows.Media.Imaging;
namespace UIForLocalizationConsecutiveApplication
{
    public partial class MainWindow : Window
    {
        private bool _mouseDown = false;
        private System.Windows.Controls.Border rect;
        private Point EndPoint;
        private int ShapeCounter = 1;      
        private int UpperCornerX = 0;
        private int UpperCornerY = 0;
        private int Width__      = 0;
        private int Height__     = 0;
        private double ConversionPixelFactor = 3.413333333333333333333333;
        private Point StartPoint = new Point(0, 0);
        private string _color_ = "#220000FF";
        private string _addressOfTextFile_;
        private int OutsideImageSelectionAndDraggingAndRelease = 0;
        public MainWindow()
        {
            InitializeComponent();
            _window_.Background = new System.Windows.Media.SolidColorBrush (
                (System.Windows.Media.Color)System.Windows.Media.ColorConverter.ConvertFromString("#f0c1e1")
			); 
        }
        private struct List_of_ROIs
        {
            public int __x;
            public int __y;
            public int __W;
            public int __H;
        }
        List_of_ROIs[] list = new List_of_ROIs[1000];
        private int ListCounter = 0;
        private void __checkConsoleTextColor()
        {
            if (Console.Foreground != System.Windows.Media.Brushes.Wheat)
            {
                Console.Foreground = System.Windows.Media.Brushes.Wheat;
            }
        }
        private void __Tracker()
        {
            __checkConsoleTextColor();
            Console.Text = "Console >\n";
            Console.Text += "A mouse click event has been detected ...\n";
            Console.ScrollToEnd();
            Console.Text += "Mouse has been clicked in x = " + UpperCornerX.ToString() + " pixel\n";
            Console.ScrollToEnd();
            Console.Text += "Mouse has been clicked in y = " + UpperCornerY.ToString() + " pixel\n";
            Console.ScrollToEnd();
            Console.Text += "x and y values have been already displayed in the related boxes.\n";
            Console.ScrollToEnd();
            Console.Text += "A mouse release event has been detected ...\n";
            Console.ScrollToEnd();
            Console.Text += "ROI is selected in x = " + UpperCornerX.ToString() + " and y = " + UpperCornerY.ToString() + "\n";
            Console.ScrollToEnd();
            Console.Text += "ROI width is = " + Width__.ToString() + " and  height is = " + Height__.ToString() + "\n";
            Console.ScrollToEnd();
            Console.Text += "-----------------------------\n";
            Console.ScrollToEnd();
            return;
        }
        private void image_MouseDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            __checkConsoleTextColor();
            _mouseDown = (e.ButtonState == System.Windows.Input.MouseButtonState.Pressed) 
                && (e.ChangedButton == System.Windows.Input.MouseButton.Left);  
            if (!_mouseDown) return;
            rect = new System.Windows.Controls.Border();          
            Console.Text += "A mouse click event has been detected ...\n";
            Console.ScrollToEnd();
            StartPoint = e.GetPosition(BackPanel);
            System.Windows.Controls.Canvas.SetLeft(rect, StartPoint.X);
            System.Windows.Controls.Canvas.SetTop (rect, StartPoint.Y);
            rect.Background = new System.Windows.Media.SolidColorBrush(
                (System.Windows.Media.Color)System.Windows.Media.ColorConverter.ConvertFromString(_color_)
            );
            rect.BorderBrush = System.Windows.Media.Brushes.Red;
            rect.BorderThickness = new Thickness(1);
            BackPanel.Children.Add(rect);
            X.Text = ((int)(StartPoint.X * ConversionPixelFactor)).ToString();
            Y.Text = ((int)(StartPoint.Y * ConversionPixelFactor)).ToString();
            UpperCornerX = (int)(StartPoint.X * ConversionPixelFactor);
            UpperCornerY = (int)(StartPoint.Y * ConversionPixelFactor);
            
            list[ListCounter].__x = UpperCornerX;
            list[ListCounter].__y = UpperCornerY;


            Console.Text += "Mouse has been clicked in x = " + UpperCornerX.ToString() + " pixel\n";
            Console.ScrollToEnd();
            Console.Text += "Mouse has been clicked in y = " + UpperCornerY.ToString() + " pixel\n";
            Console.ScrollToEnd();
            Console.Text += "x and y values have been already displayed in the related boxes.\n";
            Console.ScrollToEnd();
        }
        private void image_MouseMove(object sender, System.Windows.Input.MouseEventArgs e)
        {
            if (e.LeftButton == System.Windows.Input.MouseButtonState.Released)
                return;
            if (rect == null)
            {
                SendErrorToConsole();
                return;
            }
            var Pos = e.MouseDevice.GetPosition(BackPanel);
            var X_VALUE = Math.Min(Pos.X, StartPoint.X);
            var Y_VALUE = Math.Min(Pos.Y, StartPoint.Y);
            var _w_ = Math.Abs(Math.Max(Pos.X, StartPoint.X) - X_VALUE);
            var _h_ = Math.Abs(Math.Max(Pos.Y, StartPoint.Y) - Y_VALUE);
            rect.Width = _w_;
            rect.Height = _h_;
            System.Windows.Controls.Canvas.SetLeft(rect, X_VALUE);
            System.Windows.Controls.Canvas.SetTop(rect, Y_VALUE);
            _width.Text = (((int)(Pos.X * ConversionPixelFactor)) - UpperCornerX).ToString();
            _height.Text = (((int)(Pos.Y * ConversionPixelFactor)) - UpperCornerY).ToString();
            if ((int)((Pos.X * ConversionPixelFactor) - UpperCornerX) < 0)
            {
                Width__ = 0;
            }
            if ((int)((Pos.Y * ConversionPixelFactor) - UpperCornerY) < 0)
            {
                Height__ = 0;
            }
            if ((int)((Pos.X * ConversionPixelFactor) - UpperCornerX) >= 0)
            {
                Width__ = (int)((Pos.X * ConversionPixelFactor) - UpperCornerX);
            }
            if ((int)((Pos.Y * ConversionPixelFactor) - UpperCornerY) >= 0)
            {
                Height__ = (int)((Pos.Y * ConversionPixelFactor) - UpperCornerY);
            }
            __Tracker();
        }
        private void image_MouseUp(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            __checkConsoleTextColor();
            if (e.ChangedButton == System.Windows.Input.MouseButton.Left) _mouseDown  = false;
            if (e.ChangedButton == System.Windows.Input.MouseButton.Right) _mouseDown = false;
            if (rect == null)
            {
                SendErrorToConsole();
                return;
            }
            EndPoint = e.MouseDevice.GetPosition(BackPanel);
            rect.Background = new System.Windows.Media.SolidColorBrush (
                (System.Windows.Media.Color)System.Windows.Media.ColorConverter.ConvertFromString("#11ffff00")
            );
            rect.BorderBrush = System.Windows.Media.Brushes.BlueViolet;
            double x  = System.Windows.Controls.Canvas.GetLeft(rect);
            double y  = System.Windows.Controls.Canvas.GetTop(rect);
            double x2 = EndPoint.X;
            double y2 = EndPoint.Y;
            System.Windows.Controls.TextBlock txt = new System.Windows.Controls.TextBlock();
            txt.Margin = new Thickness(x, y, (x2 - x), (y2 - y));
            txt.Text = "ROI " + ShapeCounter.ToString();
            txt.Foreground = System.Windows.Media.Brushes.Red;
            BackPanel.Children.Add(txt);

            list[ListCounter].__W = Width__;
            list[ListCounter].__H = Height__;
            ++ListCounter;

            rect = null;
            ++ShapeCounter;
        }
        private void OpenFileDialog_Click(object sender, RoutedEventArgs e)
        {
            __checkConsoleTextColor();
            Console.Text = "";
            Console.Text += "\nBrowser opened...\n";
            Console.ScrollToEnd();
            Console.Text += "\nIt waits for a (( tif )) image to be selected.\n";
            Console.ScrollToEnd();
            Microsoft.Win32.OpenFileDialog FileToBeOpened = new Microsoft.Win32.OpenFileDialog();
            FileToBeOpened.FileName = "__"; 
            FileToBeOpened.DefaultExt = ".tif"; 
            Nullable<bool> result = FileToBeOpened.ShowDialog();
            if (result == true)
            {
                string _addressOfImageFile_ = FileToBeOpened.FileName;
                string extension = Path.GetExtension(_addressOfImageFile_);
                if (extension == ".tif")
                {
                    Console.Text += "\nImage is opening ...\n";
                    Console.ScrollToEnd();
                    _addressOfTextFile_ = _addressOfImageFile_.Substring(0, (_addressOfImageFile_.Length) - 0x04) + ".txt";
                    System.Windows.Media.ImageBrush ib = new System.Windows.Media.ImageBrush();
                    ib.ImageSource = new BitmapImage(new Uri(_addressOfImageFile_, UriKind.Relative));
                    BackPanel.Background = ib;
                    Console.Text += "Image with the address: " + _addressOfImageFile_ + " opened.\n";
                    Console.ScrollToEnd();
                    if (File.Exists(_addressOfTextFile_))
                    {
                        Console.Text += "Text file with the address: " + _addressOfTextFile_ + " copied to the application memory.\n";
                        Console.ScrollToEnd();
                    }
                    else
                    {
                        Console.Text += "Text File could not be found.\n";
                        Console.ScrollToEnd();
                    }
                }
                else
                {
                    Console.Text += "\nERROR => Only tif Images can be loaded as input\n";
                    Console.Text += "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                    Console.ScrollToEnd();
                }
            }
        }
        private void SendButton(object sender, RoutedEventArgs e)
        {
            __checkConsoleTextColor();
            System.IO.StreamWriter file = new System.IO.StreamWriter("Coordinates.txt");
            string fullPath = Path.GetFullPath("Coordinates.txt");
            file.WriteLine(_addressOfTextFile_);
            file.WriteLine(X.Text);
            file.WriteLine(Y.Text);
            file.WriteLine(_width.Text);
            file.WriteLine(_height.Text);
            file.Close();
            Console.Text = "";
            Console.Text += "\nThe last selected ROI coordination has been sent to: \n";
            Console.Text += fullPath + "\n";
            Console.ScrollToEnd();

            /*
                Run C++ Application here ...
            */
        }
        private void SendErrorToConsole()
        {
            __checkConsoleTextColor();
            Console.Text += "\n" + OutsideImageSelectionAndDraggingAndRelease.ToString() + " Error";
            Console.Text += " : Selection area was not valid.\n";
            Console.ScrollToEnd();
            Console.Text += "\n It cannot be selected outside the image area.\n";
            Console.ScrollToEnd();
            ++OutsideImageSelectionAndDraggingAndRelease;
        }
        private void CleanImageEntirely(object sender, RoutedEventArgs e)
        {
            __checkConsoleTextColor();
            if (BackPanel.Background != null)
            {
                BackPanel.Children.Clear();
                Console.Text = "\nThe entire image has been cleared from selected ROIs.\n";
                Console.ScrollToEnd();
            }
            else
            {
                Console.Text = "\nThere is no loaded image and no specified ROI(s).\n";
                Console.ScrollToEnd();
            }
            ShapeCounter = 1;
            ListCounter  = 0;
        }
        private void CleanImageLastROI(object sender, RoutedEventArgs e)
        {
            __checkConsoleTextColor();
            if (BackPanel.Background != null)
            {
                if (BackPanel.Children.Count == 2)
                {
                    BackPanel.Children.RemoveAt(BackPanel.Children.Count - 1);
                    BackPanel.Children.RemoveAt(BackPanel.Children.Count - 1);
                    --ListCounter;
                    Console.Text = "\nThe last specified ROI has been cleared from image.\n";
                    Console.ScrollToEnd();
                    X.Text       = list[BackPanel.Children.Count / 2].__x.ToString();
                    Y.Text       = list[BackPanel.Children.Count / 2].__y.ToString();
                    _width.Text  = list[BackPanel.Children.Count / 2].__W.ToString();
                    _height.Text = list[BackPanel.Children.Count / 2].__H.ToString();
                }
                else if (BackPanel.Children.Count > 2)
                {
                    BackPanel.Children.RemoveAt(BackPanel.Children.Count - 1);
                    BackPanel.Children.RemoveAt(BackPanel.Children.Count - 1);
                    --ListCounter;
                    Console.Text = "\nThe last specified ROI has been cleared from image.\n";
                    Console.ScrollToEnd();
                    X.Text       = list[(BackPanel.Children.Count / 2) - 1].__x.ToString();
                    Y.Text       = list[(BackPanel.Children.Count / 2) - 1].__y.ToString();
                    _width.Text  = list[(BackPanel.Children.Count / 2) - 1].__W.ToString();
                    _height.Text = list[(BackPanel.Children.Count / 2) - 1].__H.ToString();
                }
                else if (BackPanel.Children.Count < 2)
                {
                    Console.Text = "\nThe entire image has been cleared from selected ROIs.\n";
                    Console.ScrollToEnd();
                }
            }
            else
            {
                Console.Text = "\nThere is no loaded image and no specified ROI(s).\n";
                Console.ScrollToEnd();
            }
            if (ShapeCounter > 1)
                --ShapeCounter;
            if (BackPanel.Children.Count == 0 || BackPanel.Children.Count == 1 || BackPanel.Children.Count < 0)
            {
                for (int i = 0; i != 1000; ++i)
                {
                    list[i].__x = 0;
                    list[i].__y = 0;
                    list[i].__W = 0;
                    list[i].__H = 0;
                }
                ListCounter = 0;
            }
        }
        private void CleanConsole(object sender, RoutedEventArgs e)
        {
            __checkConsoleTextColor();
            if (Console.Text != "Console >\n")
            {
                Console.Text = "Console >\n";
                Console.ScrollToEnd();
            }
        }
        private void CleanImageAndSetToNull(object sender, RoutedEventArgs e)
        {
            __checkConsoleTextColor();
            cleanEntire.RaiseEvent(new RoutedEventArgs(System.Windows.Controls.Button.ClickEvent));
            BackPanel.Background = null;
            Console.Text += "\nImage Removed from the Application.\n";
            Console.ScrollToEnd();
            _addressOfTextFile_ = null;
        }
        private void GiveInformation(object sender, RoutedEventArgs e)
        {
            Console.Foreground = System.Windows.Media.Brushes.Red;
            Console.Text = "Software information:\n\n";
            Console.ScrollToEnd();
            Console.Text += "This software is designed fully by (Iman Abdollahzadeh), in Institute of Complex System\n";
            Console.ScrollToEnd();
            Console.Text += "ICS-4 (Cellular BioPhysics) and in Dr. Thomas Gensch research group.\n";
            Console.ScrollToEnd();
            Console.Text += "This is part of the PhD project involved in Single Molevcule Localization Microscopy (SMLM).\n";
            Console.ScrollToEnd();
            Console.Text += "\nAll rights reserved.\n";
            Console.ScrollToEnd();
            Console.Text += "\n@ 2017 - Forschungszentrum, Jülich.\n";
            Console.ScrollToEnd();
        }
        private void ShowFinalResultsFromCPPApplication()
        {
            System.Diagnostics.Process process = System.Diagnostics.Process.Start("Your CPP application.exe address");
            // get the result from a dll output of cpp application.
            // show the necessary info from that dll into your console and also make a txt file out of it.
        }
    }
}