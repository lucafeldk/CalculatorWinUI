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

    double firstNum, secondNum, result;
    std::wstring currentOperation;
    
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainWindow::run_operation() 
    {
        
        if (currentOperation == L"+") {
            result = firstNum + secondNum;
            txtFirst().Text(txtFirst().Text() + txtSecond().Text() + L"=");
            txtSecond().Text(std::to_wstring(result));
        }
        else if (currentOperation == L"-") {
            result = firstNum - secondNum;
            txtFirst().Text(txtFirst().Text() + txtSecond().Text() + L"=");
            txtSecond().Text(std::to_wstring(result));
        }
        else if (currentOperation == L"x") {
            result = firstNum * secondNum;
            txtFirst().Text(txtFirst().Text() + txtSecond().Text() + L"=");
            txtSecond().Text(std::to_wstring(result));
        }
        else if (currentOperation == L"÷") {
            result = firstNum / secondNum;
            txtFirst().Text(txtFirst().Text() + txtSecond().Text() + L"=");
            txtSecond().Text(std::to_wstring(result));
        }
        else {

        }

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
        std::wstring currentadvOperation = content.c_str();
        std::map<std::wstring, std::wstring> opConversion = {
            {L"1/x", L"1/("},
            {L"x²", L"sqr"},
            {L"√x", L"√"}
        };
        std::wstring currentFirstTxt = txtFirst().Text().c_str();
        std::wstring tempTxt = txtSecond().Text().c_str();
        double tempNumber = std::stod(tempTxt);

        // text ouput for firtText if for example √(√(x)) wants to be entered
        if (currentFirstTxt.find(opConversion[currentadvOperation]) != std::wstring::npos) {
            tempTxt = txtFirst().Text().c_str();
        }

        if (currentadvOperation == L"1/x") {
            txtFirst().Text(L"1/(" + tempTxt + L")");
            tempNumber = 1 / (tempNumber);
            txtSecond().Text(std::to_wstring(tempNumber));
        }
        else if (currentadvOperation == L"x²") {
            txtFirst().Text(L"sqr(" + tempTxt + L")");
            tempNumber = tempNumber * tempNumber;
            txtSecond().Text(std::to_wstring(tempNumber));
        }
        else if (currentadvOperation == L"√x") {
            txtFirst().Text(L"√(" + tempTxt + L")");
            tempNumber = std::sqrt(tempNumber);
            txtSecond().Text(std::to_wstring(tempNumber)); 
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
        firstNum = std::stod(equationContent.substr(0, operationIndex));
        secondNum = std::stod(txtSecond().Text().c_str());
        run_operation();
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


