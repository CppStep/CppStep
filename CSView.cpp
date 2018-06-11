//
//  CSView.cpp
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

#include "CSView.hpp"

CSRect CSView::getRect() {
#if defined(CS_Mac)
    return CSRect([toNativeView() frame]);
#elif defined(CS_Win)
    return CSRect(getOrigin(), getSize());
#endif
}

void CSView::setRect(CSRect rect) {
#if defined(CS_Mac)
    [toNativeView() setFrame: rect.toNativeRect()];
#elif defined(CS_Win)
    setOrigin(rect.origin);
    setSize(rect.size);
#endif
    relayout();
}

CSSize CSView::getSize() {
#if defined(CS_Mac)
    return CSSize([toNativeView() frame].size);
#elif defined(CS_Win)
    return CSSize(toNativeView()->Size);
#endif
}

void CSView::setSize(CSSize size) {
#if defined(CS_Mac)
    [toNativeView() setFrameSize: size.toNativeSize()];
#elif defined(CS_Win)
    toNativeView()->Size = size.toNativeSize();
#endif
    relayout();
}

CSPoint CSView::getOrigin() {
#if defined(CS_Mac)
    return CSPoint([toNativeView() frame].origin);
#elif defined(CS_Win)
    return CSPoint(toNativeView()->Location);
#endif
}

void CSView::setOrigin(CSPoint size) {
#if defined(CS_Mac)
    [toNativeView() setFrameOrigin: size.toNativePoint()];
#elif defined(CS_Win)
    toNativeView()->Location = size.toNativePoint();
#endif
    relayout();
}
