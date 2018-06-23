//
//  CSWindow.cpp
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

#include "CSWindow.hpp"

CSWindow::CSWindow(CSRect rect,
                   std::string title,
                   bool closable,
                   bool resizable
                   ) {
    std::function<void()>&& relayoutF = std::bind(&CSWindow::relayout, this);
#if defined(CS_Mac)
    nativeWindow = [[NSWindow alloc] initWithsize: rect
                                            title: title
                                       isClosable: closable
                                      isResizable: resizable
                   ];
    [nativeWindow setCallback: relayoutF];
#elif defined(CS_Win)
    nativeWindow = gcnew WinForm(rect,
                                 title,
                                 closable,
                                 resizable
                                 );
    nativeWindow->ClientSizeChanged += gcnew_WinNativeEventHandler<void>(relayoutF);
#endif
}

void CSWindow::show() {
#if defined(CS_Mac)
    [nativeWindow setHidden:NO];
#elif defined(CS_Win)
    nativeWindow->Show();
#endif
}

void CSWindow::hide() {
#if defined(CS_Mac)
    [nativeWindow setHidden:YES];
#elif defined(CS_Win)
    nativeWindow->Hide();
#endif
}

void CSWindow::presentView(CSView* view) {
    root = view;
#if defined(CS_Mac)
    [nativeWindow presentView: root];
#elif defined(CS_Win)
    nativeWindow->presentView(root);
#endif
    relayout();
}

void CSWindow::setClosingCallback(std::function<bool()> callback) {
    closingCallbackWrapper = gcnew WinWindowClosingCallbackWrapper(callback);
    nativeWindow->Closing += gcnew System::ComponentModel::CancelEventHandler(closingCallbackWrapper, &WinWindowClosingCallbackWrapper::WindowClosing);
}

void CSWindow::relayout() {
#if defined(CS_Mac)
    root->setRect(CSRect([[nativeWindow contentView] frame]));
#elif defined(CS_Win)
    root->setSize(CSSize(nativeWindow->ClientSize));
#endif
}