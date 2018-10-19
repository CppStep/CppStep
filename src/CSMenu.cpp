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

CSMenuItem::CSMenuItem(std::string title, std::function<void()> callback, CSKeyCode keyCode)
#if defined(CS_Mac)
{
    auto nKeyCode = keyCode.toNativeKeyCode();
    nativeMenuItem = [[NSMenuItem alloc] initWithTitle:@(title.c_str())
                                                action:@selector(execute)
                                         keyEquivalent:nKeyCode.first
                        ];
    nativeTarget = [[NSFunction alloc] initWithFunction:callback];
    [nativeMenuItem setTarget:nativeTarget];
    [nativeMenuItem setKeyEquivalentModifierMask:NSEventModifierFlagCommand/*nKeyCode.second*/];
}
#elif defined(CS_Win)
    : nativeMenuItem(gcnew System::Windows::Forms::ToolStripMenuItem(gcnew System::String(title.c_str()))) {
    nativeMenuItem->Click += gcnew_WinNativeEventHandler<void>(callback);
    nativeMenuItem->ShortcutKeys = keyCode.toNativeKeyCode();
}
#endif

CSMenuItem::CSMenuItem(CSSubMenu* subMenu, std::function<void()> callback, CSKeyCode keyCode) :
#if defined(CS_Mac)
    CSMenuItem(subMenu->name, callback, keyCode) {
    [nativeMenuItem setSubmenu:subMenu->toNativeMenu()];
}
#elif defined(CS_Win)
    nativeMenuItem(subMenu->toNativeMenu()) {
    nativeMenuItem->Click += gcnew_WinNativeEventHandler<void>(callback);
    nativeMenuItem->ShortcutKeys = keyCode.toNativeKeyCode();
}
#endif

CSMenuItem::CSMenuItem(NativeMenuItem nativeMenuItem) : nativeMenuItem(nativeMenuItem) {}

CSMenuItem::NativeMenuItem CSMenuItem::toNativeMenuItem() {
    return nativeMenuItem;
}
