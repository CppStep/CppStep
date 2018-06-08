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

#include "CSView.hpp"
#include "CSRect.hpp"

#if defined(CS_Mac)
#include "NSWindow.h"
#import <AppKit/AppKit.h>
#elif defined(CS_Win)
#include "WinForm.hpp"
#include "msclr\gcroot.h"
#endif

#include <string>

/** A rectangle */
struct CSRect {
    double x,
    double y,
    double width,
    double height
}

#endif /* CSRect_hpp */
