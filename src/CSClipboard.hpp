//
//  CSClipboard.hpp
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

#ifndef CSClipboard_hpp
#define CSClipboard_hpp

#include "CSCore.hpp"

#include <string>

#if defined(CS_Mac)
#import "NSString.h"
#import <AppKit/AppKit.h>
#elif defined(CS_Win)
#using <System.Windows.Forms.dll>
#include <msclr\marshal_cppstd.h>
#include <msclr\gcroot.h>
#endif

/** Accessor methods for the system clipboard */
namespace CSClipboard {

void clear();

std::string getStringValue();

void setStringValue(std::string value);

};

#endif /* CSClipboard_hpp */
