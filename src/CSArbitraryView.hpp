//
//  CSArbitraryView.hpp
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

#ifndef CSArbitraryView_hpp
#define CSArbitraryView_hpp

#include "CSCore.hpp"
#include "CSView.hpp"

#if defined(CS_Mac)
#import <AppKit/AppKit.h>
#elif defined(CS_Win)
#using <System.dll>
#using <System.Windows.Forms.dll>
#include <msclr\gcroot.h>
#endif

#include <string>

/** A label */
class CSArbitraryView : public CSView {
public:
    /** Create a CSArbitraryView
      * @param view The native view to display
      */
    CSArbitraryView(NativeView view) {
        nativeView = view;
    }

    /** Create a CSArbitraryView
      * @param view The native view to display
      */
    template <typename T>
    CSArbitraryView(msclr::gcroot<T> view) {
        T managedView = view;
        nativeView = dynamic_cast<System::Windows::Forms::Control^>(managedView);
    }

    typedef CSView::NativeView NativeView;
    virtual CSView::NativeView toNativeView() {
        return nativeView;
    }
private:
    NativeView nativeView;
};

#endif /* CSArbitraryView_hpp */
