//
//  CSWindow.hpp
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

#ifndef CSWindow_hpp
#define CSWindow_hpp

#include "CSCore.hpp"
#include "CSView.hpp"
#include "CSRect.hpp"

#if defined(CS_Mac)
#include "NSWindow.h"
#import <AppKit/AppKit.h>
#elif defined(CS_Win)
#include "WinForm.hpp"
#include "WinNativeEventHandler.hpp"
#include <msclr\gcroot.h>
#endif

#include <functional>
#include <string>

/** A window containing a root view */
class CSWindow {
public:
    CSWindow(CSRect rect,
             std::string title,
             bool closable,
             bool resizable
             );

    void presentView(CSView* view);

    void relayout();

#if defined(CS_Mac)
    typedef NSWindow* NativeWindow;
#elif defined(CS_Win)
    typedef msclr::gcroot<WinForm^> NativeWindow;
#endif

private:
    CSView* root;
    NativeWindow nativeWindow;
};

#endif /* CSWindow_hpp */
