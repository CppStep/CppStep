//
//  CSAlignView.hpp
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

#ifndef CSAlignView_hpp
#define CSAlignView_hpp

#include "CSCore.hpp"
#include "CSView.hpp"
#include "CSSuperView.hpp"

#if defined(CS_Mac)
#import <AppKit/AppKit.h>
#elif defined(CS_Win)
#using <System.dll>
#using <System.Windows.Forms.dll>
#include <msclr\gcroot.h>
#endif

#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>

/** A view displaying a web page */
class CSAlignView : public CSView {
public:
    enum class Direction {Horizontal, Vertical};

    CSAlignView(Direction dir) : CSAlignView(CSRect(), dir) {}
    CSAlignView(CSRect rect, Direction dir);

    void addView(CSView* subView, bool expanding);

    virtual void relayout();

    typedef CSSuperView::NativeView NativeView;
    virtual CSView::NativeView toNativeView();
private:
    Direction dir;

    std::vector<std::pair<CSView*, bool>> subViews;

    CSSuperView* superView;

    double fixedLength;
};

#endif /* CSAlignView_hpp */
