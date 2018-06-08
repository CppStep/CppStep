//
//  CSLabel.hpp
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

#ifndef CSLabel_hpp
#define CSLabel_hpp

#if defined(CS_Mac)
#import <AppKit/AppKit.h>
#elif defined(CS_Win)
#using <System.Windows.Forms.dll>
#include "msclr\gcroot"
#endif

#include <string>

/** A view displaying a web page */
class CSLabel {
public:
    CSLabel(std::string text);

#if defined(CS_Mac)
    typedef NSTextField* NativeView;
#elif defined(CS_Win)
    typedef msclr::gcroot<System::Windows::Forms::Label^> NativeView;
#endif
    virtual NativeView toNativeView();
private:
    NativeView nativeView;
};

#endif /* CSLabel_hpp */
