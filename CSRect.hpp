//
//  CSRect.hpp
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

#ifndef CSRect_hpp
#define CSRect_hpp

/** A rectangle */
struct CSRect {
    double x;
    double y;
    double width;
    double height;

#if defined(CS_Mac)
    typedef NSRect NativeRect;
#elif defined(CS_Win)
    typedef void NativeRect;
#endif

    NativeRect toNativeRect() {
#if defined(CS_Mac)
        return NSMakeRect(this->x,
                          this->y,
                          this->width,
                          this->height
                          );
#elif defined(CS_Win)
#endif
    }
};

#endif /* CSRect_hpp */
