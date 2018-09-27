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
#include "CSMenu.hpp"
#include "CSAlignView.hpp"
#include "CSArbitraryView.hpp"

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

#if defined(CS_Win)
ref class WinWindowClosingCallbackWrapper {
private:
    std::function<bool()>* callback;
public:
    WinWindowClosingCallbackWrapper(std::function<bool()> callbackTMP) {
        callback = new std::function<bool()>(callbackTMP);
    }

    void WindowClosing(Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
        e->Cancel = !(*callback)();
    }
};
#endif

/** A window containing a root view */
class CSWindow {
public:
    /** Create a CSWindow
      * @param rect      The frame for the window
      * @param title     The title for the window
      * @param closable  Whether the window has a close button
      * @param resizable Whether the window can be manually resized
      */
    CSWindow(CSRect rect,
             std::string title,
             bool closable,
             bool resizable
             );

    /** Show the window */
    void show();
    /** Hide the window.
      * This does not delete the window so the window can be restored.
      */
    void hide();

    /** Change the main view
      * @param view    The view to show
      * @param menuBar The menu bar to show
      */
    void presentView(CSView* view, CSMenuBar* menuBar = nullptr);

    /** Set a callback to be called when the window is about to close
      * @param callback The callback that is called when the window is about to close.
      *                 It should return true if the window should be allowed to close.
      *                 If this returns true the window will not be able to be opened again.
      */
    void setClosingCallback(std::function<bool()> callback);

    /** Relayout the view.
      * This is called when the window is resized.
      */
    void relayout();

#if defined(CS_Mac)
    typedef NSWindow* NativeWindow;
#elif defined(CS_Win)
    typedef msclr::gcroot<WinForm^> NativeWindow;
#endif

private:
    CSView* root;
    NativeWindow nativeWindow;
#if defined(CS_Mac)
    CSWindowCallbacks* nativeDelegate;
#elif defined(CS_Win)
    msclr::gcroot<WinWindowClosingCallbackWrapper^> closingCallbackWrapper;
#endif
};

#endif /* CSWindow_hpp */
