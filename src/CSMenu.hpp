//
//  CSMenu.hpp
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

#ifndef CSMenu_hpp
#define CSMenu_hpp

#include "CSCore.hpp"
#include "CSKeyCode.hpp"

#if defined(CS_Mac)
#import <AppKit/AppKit.h>
#elif defined(CS_Win)
#include "WinNativeEventHandler.hpp"
#using <System.dll>
#using <System.Windows.Forms.dll>
#include <msclr\gcroot.h>
#endif

#include <functional>
#include <string>
#include <type_traits>

#if defined(CS_Mac)
class CSMenu;

typedef CSMenu CSMenuBar;
typedef CSMenu CSContextMenu;
typedef CSMenu CSSubMenu;
#elif defined(CS_Win)
template <bool, bool> class CSMenu;

typedef CSMenu<true, false> CSMenuBar;
typedef CSMenu<true, true> CSContextMenu;
typedef CSMenu<false, false> CSSubMenu;
#endif

class CSMenuItem {
public:
    CSMenuItem(std::string title, std::function<void()> callback = [](){}, CSKeyCode keyCode = CSKeyCode());
    CSMenuItem(CSSubMenu* subMenu, std::function<void()> callback = [](){}, CSKeyCode keyCode = CSKeyCode());

#if defined(CS_Mac)
    typedef NSMenuItem* NativeMenuItem;
#elif defined(CS_Win)
    typedef msclr::gcroot<System::Windows::Forms::ToolStripMenuItem^> NativeMenuItem;
#endif
    virtual NativeMenuItem toNativeMenuItem();
private:
    NativeMenuItem nativeMenuItem;

#if defined(CS_Mac)
    CSMenuItem(std::string name, CSKeyCode keyCode);
#endif
};

/** A menu bar. */
#if defined(CS_Win)
template <bool isTopLevel = true, bool isContextMenu = false>
#endif
class CSMenu {
public:
#if defined(CS_Mac)
    typedef NSMenu* NativeMenu;
#elif defined(CS_Win)
    typedef typename std::conditional<isTopLevel,
                                      typename std::conditional<isContextMenu,
                                                                msclr::gcroot<System::Windows::Forms::ContextMenuStrip^>,
                                                                msclr::gcroot<System::Windows::Forms::MenuStrip^>>::type,
                                      msclr::gcroot<System::Windows::Forms::ToolStripMenuItem^>>::type NativeMenu;
#endif
private:
    NativeMenu nativeMenu;
public:
    const std::string name;
    
    CSMenu(std::string name = "")
#if defined(CS_Mac)
        : nativeMenu([[NSMenu alloc] initWithTitle:@(name.c_str())]),
          name(name) {}
#elif defined(CS_Win)
    {
        if constexpr (isTopLevel) {
            if constexpr (isContextMenu) {
                nativeMenu = gcnew System::Windows::Forms::ContextMenuStrip();
            } else {
                nativeMenu = gcnew System::Windows::Forms::MenuStrip();
            }
            nativeMenu->Name = gcnew System::String(name.c_str());
        } else {
            nativeMenu = gcnew System::Windows::Forms::ToolStripMenuItem(gcnew System::String(name.c_str()));
        }
    }
#endif

    virtual NativeMenu toNativeMenu() {
        return nativeMenu;
    }

    void addItem(CSMenuItem* item) {
#if defined(CS_Mac)
        [nativeMenu addItem:item->toNativeMenuItem()];
#elif defined(CS_Win)
        if constexpr (isTopLevel) {
            nativeMenu->Items->Add(item->toNativeMenuItem());
        } else {
            nativeMenu->DropDownItems->Add(item->toNativeMenuItem());
        }
#endif
    }

    void addItems(CSMenuItem* item) {
        addItem(item);
    }

    void addSubMenu(CSSubMenu* subMenu, std::function<void()> callback = [](){}, CSKeyCode keyCode = CSKeyCode()) {
        addItem(new CSMenuItem(subMenu, callback, keyCode));
    }

    template <typename...Items>
    void addItems(CSMenuItem* item, Items...items) {
        addItem(item);
        addItems(items...);
    }
};

#endif /* CSMenu_hpp */
