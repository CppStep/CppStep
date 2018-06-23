//
//  CSLabel.cpp
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

#include "CSLabel.hpp"

CSLabel::CSLabel(std::string text) {
#if defined(CS_Mac)
    nativeView = [[NSTextField alloc] initWithFrame:NSZeroRect];
    [nativeView setStringValue: @(text.c_str())];
    [nativeView setEditable:NO];
    [nativeView setSelectable:NO];
    [nativeView setBordered:NO];
    [nativeView setBackgroundColor:[NSColor clearColor]];
#elif defined(CS_Win)
    nativeView = gcnew System::Windows::Forms::Label();
    nativeView->Text = gcnew System::String(text.c_str());
    nativeView->AutoSize = true;
#endif
}

CSView::NativeView CSLabel::toNativeView() {
  #if defined(CS_Mac)
  return this->nativeView;
  #elif defined(CS_Win)
  return safe_cast<CSView::NativeView>(this->nativeView);
  #endif
}
