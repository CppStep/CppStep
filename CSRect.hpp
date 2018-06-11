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

#include "CSCore.hpp"

#if defined(CS_Mac)
#import <Foundation/Foundation.h>
#elif defined(CS_Win)
#using <System.Drawing.dll>
#include <msclr\gcroot.h>
#endif

/** A point */
struct CSPoint {
    double x;
    double y;

    CSPoint() : x(0), y(0) {}
    CSPoint(double x, double y) : x(x), y(y) {}

#if defined(CS_Mac)
    typedef NSPoint NativePoint;
#elif defined(CS_Win)
    typedef System::Drawing::Point NativePoint;
#endif

    CSPoint(NativePoint point) {
#if defined(CS_Mac)
        this->x = point.x;
        this->y = point.y;
#elif defined(CS_Win)
        this->x = point.X;
        this->y = point.Y;
#endif
    }

    NativePoint toNativePoint() {
#if defined(CS_Mac)
        return NSMakePoint(this->x,
                           this->y
                           );
#elif defined(CS_Win)
return System::Drawing::Point(this->x,
                              this->y
                              );
#endif
    }
};

/** A size */
struct CSSize {
    double width;
    double height;

    CSSize() : width(0), height(0) {}
    CSSize(double w, double h) : width(w), height(h) {}

#if defined(CS_Mac)
    typedef NSSize NativeSize;
#elif defined(CS_Win)
    typedef System::Drawing::Size NativeSize;
#endif

    CSSize(NativeSize size) {
#if defined(CS_Mac)
        this->width = size.width;
        this->height = size.height;
#elif defined(CS_Win)
        this->width = size.Width;
        this->height = size.Height;
#endif
    }

    NativeSize toNativeSize() {
#if defined(CS_Mac)
        return NSMakeSize(this->width,
                          this->height
                          );
#elif defined(CS_Win)
        return System::Drawing::Size(this->width,
                                     this->height
                                     );
#endif
    }
};

/** A rectangle */
struct CSRect {
    CSPoint origin;
    CSSize size;

    CSRect() : origin(), size() {}
    CSRect(CSPoint o, CSSize s) : origin(o), size(s) {}
    CSRect(double x, double y, double w, double h) : CSRect(CSPoint(x, y), CSSize(w, h)) {}

#if defined(CS_Mac)
    typedef NSRect NativeRect;
#elif defined(CS_Win)
    typedef CSRect NativeRect;
#endif

#if defined(CS_Mac)
    CSRect(NativeRect rect) : origin(rect.origin), size(rect.size) {}
#elif defined(CS_Win)
#endif

    NativeRect toNativeRect() {
#if defined(CS_Mac)
        return NSMakeRect(this->origin.x,
                          this->origin.y,
                          this->size.width,
                          this->size.height
                          );
#elif defined(CS_Win)
        return *this;
#endif
    }
};

#endif /* CSRect_hpp */
