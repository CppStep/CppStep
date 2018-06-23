//
//  CSTextField.hpp
//  CppStep
//
//  Copyright � 2018 Jonathan Tanner. All rights reserved.
//
//This file is part of CppStep.
//
//CppStep is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//CppStep is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with CppStep.  If not, see <http://www.gnu.org/licenses/>.

#ifndef CSTextField_hpp
#define CSTextField_hpp

#include "CSCore.hpp"
#include "CSView.hpp"
#include "CSRect.hpp"

#if defined(CS_Mac)
#import <AppKit/AppKit.h>
#elif defined(CS_Win)
#include "WinNativeEventHandler.hpp"
#using <System.dll>
#using <System.Windows.Forms.dll>
#include <msclr\gcroot.h>
#include <msclr\marshal_cppstd.h>
#endif

#include <string>
#include <functional>

#if defined(CS_Win)
ref class WinTextFieldCallbackWrapper {
private:
    std::function<bool(std::string)>* callback;

    void callCallback(System::Object^ sender) {
        (*callback)(msclr::interop::marshal_as<std::string>(dynamic_cast<System::Windows::Forms::TextBox^>(sender)->Text));
    }
public:
    WinTextFieldCallbackWrapper(std::function<bool(std::string)> callbackTMP) {
        callback = new std::function<bool(std::string)>(callbackTMP);
    }

    void leave(System::Object^ sender, System::EventArgs^ e) {
        callCallback(sender);
    }

    void enterKey(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
        if (e->KeyCode == System::Windows::Forms::Keys::Enter) {
            callCallback(sender);
        }
    }
};
#endif

/** A text field */
class CSTextField : public CSView {
public:
    /** Create a CSTextField with zero size */
    CSTextField() : CSTextField(CSRect()) {}
    /** Create a CSTextField
      * @param rect The frame for the view
      */
    CSTextField(CSRect rect);

    /** Get the contents of the field
      * @return The string value in the field
      */
    std::string getText();
    /** Set the contents of the field
      * @param text The new string value to be put in the field
      */
    void setText(std::string text);

    void setCallback(std::function<bool(std::string)> callback);

#if defined(CS_Mac)
    typedef NSTextField* NativeView;
#elif defined(CS_Win)
    typedef msclr::gcroot<System::Windows::Forms::TextBox^> NativeView;
#endif
    virtual CSView::NativeView toNativeView();
private:
    NativeView nativeView;
#if defined(CS_Win)
    msclr::gcroot<WinTextFieldCallbackWrapper^> callbackWrapper;
#endif
};

#endif /* CSTextField_hpp */
