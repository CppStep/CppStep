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
    /** The x-ordinate of the point */
    double x;
    /** The y-ordinate of the point */
    double y;

    /** Create a point at the origin */
    CSPoint() : x(0), y(0) {}
    /** Create a point with the given coordinates */
    CSPoint(double x, double y) : x(x), y(y) {}

#if defined(CS_Mac)
    typedef NSPoint NativePoint;
#elif defined(CS_Win)
    typedef System::Drawing::Point NativePoint;
#endif

    /** Create a CSPoint with the given NativePoint */
    CSPoint(NativePoint point) {
#if defined(CS_Mac)
        this->x = point.x;
        this->y = point.y;
#elif defined(CS_Win)
        this->x = point.X;
        this->y = point.Y;
#endif
    }

    /** Create a NativePoint from this CSPoint */
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

    /** Create a zero size */
    CSSize() : width(0), height(0) {}
    /** Create a size
      * @param w The width
      * @param h The height
      */
    CSSize(double w, double h) : width(w), height(h) {}

#if defined(CS_Mac)
    typedef NSSize NativeSize;
#elif defined(CS_Win)
    typedef System::Drawing::Size NativeSize;
#endif

    /** Create a CSSize with the given NativeSize */
    CSSize(NativeSize size) {
#if defined(CS_Mac)
        this->width = size.width;
        this->height = size.height;
#elif defined(CS_Win)
        this->width = size.Width;
        this->height = size.Height;
#endif
    }

    /** Create a NativeSize from this CSSize */
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
    /** The top left corner of the CSRect */
    CSPoint origin;
    CSSize size;

    /** Create a zero rectangle */
    CSRect() : origin(), size() {}
    /** Create a CSRect
      * @param o The origin (top left corner)
      * @param s The size
      */
    CSRect(CSPoint o, CSSize s) : origin(o), size(s) {}
    /** Create a CSRect
      * @param x The x-ordinate of the top left corner
      * @param y The y-ordinate of the top left corner
      * @param w The width
      * @param h The height
      */
    CSRect(double x, double y, double w, double h) : CSRect(CSPoint(x, y), CSSize(w, h)) {}

#if defined(CS_Mac)
    typedef NSRect NativeRect;
#elif defined(CS_Win)
    typedef CSRect NativeRect;
#endif

    /** Create a CSRect with the given NativeRect */
#if defined(CS_Mac)
    CSRect(NativeRect rect) : origin(rect.origin), size(rect.size) {}
#elif defined(CS_Win)
#endif

    /** Create a NativeRect from this CSRect */
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
