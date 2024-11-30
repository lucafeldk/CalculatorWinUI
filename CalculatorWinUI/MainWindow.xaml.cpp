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
    bool isFirstNum = true;
    bool isChangeable = true;
    std::wstring operationText = L"";
    
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainWindow::run_operation(std::wstring equationText) 
    {
        // run basic math operations
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
        currentOperation = L""; //reset the operation
        isFirstNum = true;
        isChangeable = true;
  
    }

    void MainWindow::number_Button(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        // Number 0-9 pressed
        auto button = sender.as<winrt::Microsoft::UI::Xaml::Controls::Button>();
        auto content = button.Content().as<hstring>();
        std::wstring currentSecondTxt = txtSecond().Text().c_str();
        
        // if there is a equation already input
        if (txtFirst().Text().c_str() != L"" && isChangeable) {
            txtSecond().Text(L"");
            isChangeable = false;
        }
      
        //display number and save as first or second Number
        txtSecond().Text(txtSecond().Text() + content);     
        if (content == L".") {
            return;
        }

        if (isFirstNum) {
            txtFirst().Text(L"");
            firstNum = std::stod(txtSecond().Text().c_str());
        }
        else {
            secondNum = std::stod(txtSecond().Text().c_str());
        }
    }

    void MainWindow::mainops_Button(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        // Main math operations pressed (+-÷x)
        auto button = sender.as<winrt::Microsoft::UI::Xaml::Controls::Button>();
        auto content = button.Content().as<hstring>();
        isChangeable = true;
        
        //when firstNum is not set yet
        if (isFirstNum) {
            firstNum = std::stod(txtSecond().Text().c_str());
            isFirstNum = false;
        }

        //save currentOperation and display current equation 
        currentOperation = content.c_str();
        txtFirst().Text(txtSecond().Text() + content);
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
        
        // for repeated operation like √(√(x)), if a advanced operation is already in the equation
        for (const std::pair<const std::wstring, std::wstring>& pair : opConversion) {
            if (currentFirstTxt.find(opConversion[pair.first]) != std::wstring::npos) {
                tempTxt = operationText;
            }
        }

        // operation and secondText Manipulation
        if (currentadvOperation == L"1/x") {
            operationText = L"1/(" + tempTxt + L")";
            tempNumber = 1 / (tempNumber);
        }
        else if (currentadvOperation == L"x²") {
            operationText = L"sqr(" + tempTxt + L")";
            tempNumber = tempNumber * tempNumber;
        }
        else if (currentadvOperation == L"√x") {
            operationText = L"√(" + tempTxt + L")";
            tempNumber = std::sqrt(tempNumber);
        }
        else {
            // percent
        }
        
        txtSecond().Text(std::to_wstring(tempNumber));
        if (isFirstNum) {
            txtFirst().Text(operationText);
            firstNum = tempNumber;
        }
        else {
            txtFirst().Text(std::to_wstring(firstNum) + currentOperation + operationText);
            secondNum = tempNumber;
        }

        
    }
    
    void MainWindow::result_Button(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        // Result operator (=) pressed
        isFirstNum = true;
        operationText = L"";
        winrt::hstring txtHstr = txtFirst().Text();
        std::wstring equationContent = txtHstr.c_str();
        int operationIndex = equationContent.find(currentOperation);
        run_operation(equationContent);
    }
    
    void MainWindow::delete_Button(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        // delete operations C,CE,DEL
        auto button = sender.as<winrt::Microsoft::UI::Xaml::Controls::Button>();
        std::wstring wstrContent = button.Content().as<hstring>().c_str();
        
        if (wstrContent == L"C") {
            txtFirst().Text(L"");
            txtSecond().Text(L"");

            //reset necessary parmeters
            currentOperation = L"";
            isFirstNum = true;
            isChangeable = true;
            operationText = L"";
        }
        else if (wstrContent == L"CE") {
            txtSecond().Text(L"");
        }
        else if(wstrContent == L"DEL"){
            // delete one char/num on equation
            std::wstring tmpString = txtSecond().Text().c_str();
            tmpString = tmpString.substr(0, tmpString.size() - 1);
            txtSecond().Text(tmpString);
            
            //reset necessary parmeters if operator was deleted
            if (tmpString.find(currentOperation) == std::wstring::npos) {
                currentOperation = L"";
                isFirstNum = true;
                isChangeable = true;
            }
        }
    }
}


