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

CSWindow::CSWindow(CSView* view,
                   CSRect rect,
                   std::string title,
                   bool closable,
                   bool resizable
                   ) {
    root = view;
#if defined(CS_Mac)
    nativeWindow = [[NSWindow alloc] initWithCSView: view
                                               size: rect
                                              title: title
                                         isClosable: closable
                                        isResizable: resizable
                   ];
#elif defined(CS_Win)
    nativeWindow = CForm(view,
                         rect,
                         title,
                         closable,
                         resizable
                         )
#endif
}

void CSWindow::presentView(CSView* view) {
    root = view;
#if defined(CS_Mac)
    [nativeWindow presentView: root];
#elif defined(CS_Win)
    nativeWindow->Controls->Clear();
    nativeWindow->Controls->Add(nativeRoot);
#endif
}

