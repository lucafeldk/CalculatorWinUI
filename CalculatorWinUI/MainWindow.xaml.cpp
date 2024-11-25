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
    std::wstring currentOperation;
    
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
        if (txtFirst().Text().c_str() != L"") {
            txtSecond().Text(L"");
        }
        txtSecond().Text(txtSecond().Text() + content);
    }

    void MainWindow::mainops_Button(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        // Main math operations pressed (+-÷x)
        auto button = sender.as<winrt::Microsoft::UI::Xaml::Controls::Button>();
        auto content = button.Content().as<hstring>();
        txtFirst().Text(txtSecond().Text() + content);
        currentOperation = content.c_str();
    }

    void MainWindow::advops_Button(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        // Main math operations pressed (1/x,x²,√x)
        auto button = sender.as<winrt::Microsoft::UI::Xaml::Controls::Button>();
        auto content = button.Content().as<hstring>();
        currentOperation = content.c_str();

        if (currentOperation == L"1/x") {
            txtFirst().Text(L"1/(" + txtSecond().Text() + L")");
        }
        else if (currentOperation == L"x²") {
            txtFirst().Text(L"sqr(" + txtSecond().Text() + L")");
        }
        else if (currentOperation == L"√x") {
            txtFirst().Text(L"√(" + txtSecond().Text() + L")");
        }
        else {
            // percent
        }
        
    }
    
    void MainWindow::result_Button(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        // Result operator (=) pressed
        winrt::hstring txtHstr = txtFirst().Text();
        std::wstring equationContent = txtHstr.c_str();
        int operationIndex = equationContent.find(currentOperation);
        firstNum = std::stoi(equationContent.substr(0,operationIndex));
        secondNum = std::stoi(txtSecond().Text().c_str());

        if (currentOperation == L"+")
        {
            result = firstNum + secondNum;
            txtFirst().Text(txtFirst().Text() + txtSecond().Text() + L"=");
            txtSecond().Text(std::to_wstring(result));
        }
        else if (currentOperation == L"-")
        {
            result = firstNum - secondNum;
            txtFirst().Text(txtFirst().Text() + txtSecond().Text() + L"=");
            txtSecond().Text(std::to_wstring(result));
        }
        else if (currentOperation == L"x")
        {
            result = firstNum * secondNum;
            txtFirst().Text(txtFirst().Text() + txtSecond().Text() + L"=");
            txtSecond().Text(std::to_wstring(result));
        }
        else if (currentOperation == L"÷")
        {
            result = firstNum / secondNum;
            txtFirst().Text(txtFirst().Text() + txtSecond().Text() + L"=");
            txtSecond().Text(std::to_wstring(result));
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


