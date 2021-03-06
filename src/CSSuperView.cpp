//
//  CSSuperView.cpp
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

#include "CSSuperView.hpp"

CSSuperView::CSSuperView(CSRect rect) {
#if defined(CS_Mac)
    nativeView = [[NSView alloc] initWithFrame:rect.toNativeRect()];
#elif defined(CS_Win)
    nativeView = gcnew System::Windows::Forms::Panel();
    nativeView->Location = rect.origin.toNativePoint();
    nativeView->Size = rect.size.toNativeSize();
#endif
}

void CSSuperView::addView(CSView* subView) {
    CSView::NativeView nativeSubView = subView->toNativeView();
#if defined(CS_Mac)
    [nativeView addSubview: nativeSubView];
#elif defined(CS_Win)
    nativeView->Controls->Add(nativeSubView);
#endif
}

CSView::NativeView CSSuperView::toNativeView() {
#if defined(CS_Mac)
    return this->nativeView;
#elif defined(CS_Win)
    return safe_cast<CSView::NativeView>(this->nativeView);
#endif
}
