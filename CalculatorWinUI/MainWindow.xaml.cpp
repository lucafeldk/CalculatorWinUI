#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include <iostream>

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
        // Number 0-9 pressed
        auto button = sender.as<winrt::Microsoft::UI::Xaml::Controls::Button>();
        auto content = button.Content().as<hstring>();
        txtSecond().Text(txtSecond().Text()+ content);
    }

    void MainWindow::mainops_Button(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        // Main math operations pressed (+-/x)
 
    }

    void MainWindow::result_Button(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        // Result operator (=) pressed
        winrt::hstring txtHstr = txtFirst().Text();
        std::wstring equationContent = txtHstr.c_str();

        if (equationContent.find(L"+")!= std::wstring::npos)
        {
            txtFirst().Text(txtFirst().Text() + txtSecond().Text());
        }
        else if (equationContent.find(L"-") != std::wstring::npos)
        {

        }
        else if (equationContent.find(L"x") != std::wstring::npos)
        {

        }
        else if (equationContent.find(L"/") != std::wstring::npos)
        {

        }
        else 
        {

        }
    }
    
    void MainWindow::delete_Button(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        // delete operations C,CE,DEL
        auto button = sender.as<winrt::Microsoft::UI::Xaml::Controls::Button>();
        std::wstring wstrContent = button.Content().as<hstring>().c_str();
        
        if (wstrContent == L"C") {

            txtSecond().Text(L"0");
        }
        else if (wstrContent == L"CE") {
            txtSecond().Text(L"0");
            txtFirst().Text(L"");
        }
        else if(wstrContent == L"DEL"){
            std::wstring tmpString = txtSecond().Text().c_str();
            tmpString = tmpString.substr(0, tmpString.size() - 1);
            txtSecond().Text(tmpString);
        }
    }



}


