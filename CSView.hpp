//
//  CSView.hpp
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

#ifndef CSView_hpp
#define CSView_hpp

#include "CSCore.hpp"
#include "CSRect.hpp"

#if defined(CS_Mac)
#import <AppKit/AppKit.h>
#elif defined(CS_Win)
#using <System.dll>
#using <System.Windows.Forms.dll>
#include <msclr\gcroot.h>
#endif

/** A view displaying a web page */
class CSView {
public:
    CSRect getRect();
    void setRect(CSRect rect);

    CSSize getSize();
    void setSize(CSSize size);

    double getWidth() { return getSize().width; }
    double getHeight() { return getSize().height; }
    void setWidth(double width) { setSize(CSSize(width, getHeight())); }
    void setHeight(double height) { setSize(CSSize(getWidth(), height)); }

    CSPoint getOrigin();
    void setOrigin(CSPoint origin);

    double getX() { return getOrigin().x; }
    double getY() { return getOrigin().y; }
    void setX(double x) { setOrigin(CSPoint(x, getY())); }
    void setY(double y) { setOrigin(CSPoint(getX(), y)); }

    virtual void relayout() {}

    #if defined(CS_Mac)
        typedef NSView* NativeView;
    #elif defined(CS_Win)
        typedef msclr::gcroot<System::Windows::Forms::Control^> NativeView;
    #endif
    virtual NativeView toNativeView() = 0;
};

#endif /* CSView_hpp */
