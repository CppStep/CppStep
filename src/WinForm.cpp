//
//  WinForm.cpp
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

#include "WinForm.hpp"

WinForm::WinForm(CSRect rect,
                 std::string title,
                 bool closable,
                 bool resizable
                 ) {
    this->Name = gcnew System::String(title.c_str());
    this->Text = gcnew System::String(title.c_str());
    this->Size = rect.size.toNativeSize();
    this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
    this->Location = rect.origin.toNativePoint();

    if (!closable) {
        this->ControlBox = false;
    }

    if (resizable) {
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
    } else {
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
    }

    this->Show();
}

void WinForm::presentView(CSView* view) {
    this->Controls->Clear();
    this->Controls->Add(view->toNativeView());
}
