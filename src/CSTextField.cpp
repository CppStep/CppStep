//
//  CSTextField.cpp
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

#include "CSTextField.hpp"

CSTextField::CSTextField(CSRect rect) {
#if defined(CS_Mac)
    nativeView = [[NSTextField alloc] initWithFrame:rect.toNativeRect()];
    [nativeView setEditable:YES];
#elif defined(CS_Win)
    nativeView = gcnew System::Windows::Forms::TextBox();
    nativeView->Location = rect.origin.toNativePoint();
    nativeView->Size = rect.size.toNativeSize();
#endif
}

std::string CSTextField::getText() {
  #if defined(CS_Mac)
      return std::string([[nativeView stringValue] cStringUsingEncoding: NSUTF8StringEncoding]);
  #elif defined(CS_Win)
      return msclr::interop::marshal_as<std::string>(nativeView->Text);
  #endif
}

void CSTextField::setText(std::string text) {
#if defined(CS_Mac)
    [nativeView setStringValue: @(text.c_str())];
#elif defined(CS_Win)
    nativeView->Text = gcnew System::String(text.c_str());
#endif
}

void CSTextField::setCallback(std::function<bool(std::string)> callback) {
#if defined(CS_Mac)
    [nativeView setCallback: callback];
#elif defined(CS_Win)
    callbackWrapper = gcnew WinTextFieldCallbackWrapper(callback);
    nativeView->Leave += gcnew System::EventHandler(callbackWrapper, &WinTextFieldCallbackWrapper::leave);
    nativeView->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(callbackWrapper, &WinTextFieldCallbackWrapper::enterKey);
#endif
}

CSView::NativeView CSTextField::toNativeView() {
  #if defined(CS_Mac)
  return this->nativeView;
  #elif defined(CS_Win)
  return safe_cast<CSView::NativeView>(this->nativeView);
  #endif
}
