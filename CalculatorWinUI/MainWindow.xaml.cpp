#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CalculatorWinUI::implementation
{

    int firstNum, secondNum, result;
    
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainWindow::number_Button(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto button = sender.as<winrt::Microsoft::UI::Xaml::Controls::Button>();
        auto content = button.Content().as<hstring>();
        txtSecond().Text(content);
    }

    /*
    void MainWindow::conversion() 
    {
        firstNum = stoi(to_string(txtFirst().Text()));
        secondNum = stoi(to_string(txtSecond().Text()));
    }
    
    void MainWindow::output() 
    {
        lblResult().Text(L"Result " + to_hstring(result));
    }

    void MainWindow::add(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        conversion();
        result = firstNum + secondNum;
        output();
    }

    void MainWindow::subtract(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        conversion();
        result = firstNum - secondNum;
        output();
    }

    void MainWindow::multiply(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        conversion();
        result = firstNum * secondNum;
        output();
    }

    void MainWindow::divide(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        conversion();
        result = firstNum / secondNum;
        output();
    }*/

}


