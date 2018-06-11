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
    std::function<void()> relayoutF = std::bind(&CSWindow::relayout, this);
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
    WinNativeFunctionWrapper^ wrapper = gcnew WinNativeFunctionWrapper(relayoutF);
    nativeWindow->ClientSizeChanged += gcnew System::EventHandler(wrapper, &WinNativeFunctionWrapper::callFunction);

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

void CSWindow::relayout() {
#if defined(CS_Mac)
    root->setRect(CSRect([[nativeWindow contentView] frame]));
#elif defined(CS_Win)
    root->setSize(CSSize(nativeWindow->ClientSize));
    root->setOrigin(CSPoint(nativeWindow->Location));
#endif
}
