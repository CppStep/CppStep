//
//  CSWebView.cpp
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

#include "CSWebView.hpp"

CSWebView::CSWebView(std::string contentsTMP) {
    contents = contentsTMP;
}

CSWebView::NativeView CSWebView::toNativeView() {
#if defined(CS_Mac)
    WkWebView* nativeView = [[WkWebView alloc] initWithFrame: [CGRect zero]];
    [nativeView loadHTMLString: @(contents.c_str()) baseURL: [NSURL URLWithString: @"/"]];
#elif defined(CS_Win)
    NativeView nativeView = gcnew System::Windows::Forms::WebBrowser();
    nativeView->NavigateToString(gcnew String(contents))
#endif
    return nativeView;
}

