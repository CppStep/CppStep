//
//  CSMenu.cpp
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

#include "CSMenu.hpp"

CSMenuItem::CSMenuItem(CSSubMenu* subMenu, CSKeyCode keyCode, std::function<void()> callback) :
#if defined(CS_Mac)
    CSMenuItem(subMenu->name, keyCode) {
    [nativeMenuItem setSubMenu:subMenu->toNativeMenu()];
}
#elif defined(CS_Win)
    nativeMenuItem(subMenu->toNativeMenu()) {
        nativeMenuItem->Click += gcnew_WinNativeEventHandler<void>(callback);
    }
#endif

CSMenuItem::NativeMenuItem CSMenuItem::toNativeMenuItem() {
    return nativeMenuItem;
}

#if defined(CS_Mac)
void CSMenuItem::CSMenuItem(std::string name, CSKeyCode keyCode) :
    nativeMenuItem([[NSMenuItem alloc] initWithTitle:@(name.c_str())
                                              action:nil
                                       keyEquivalent:keyCode->toNativeKeyCode()
                    ]) {}
#endif
