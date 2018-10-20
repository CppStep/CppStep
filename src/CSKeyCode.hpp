//
//  CSKeyCode.hpp
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

#ifndef CSKeyCode_hpp
#define CSKeyCode_hpp

#include "CSCore.hpp"

#include <utility>

#if defined(CS_Mac)
#import "NSString.h"
#import <AppKit/AppKit.h>
#elif defined(CS_Win)
#using <System.Windows.Forms.dll>
#include <msclr\gcroot.h>
#endif

#include <string>

/** A key code */
struct CSKeyCode {
public:
#if defined(CS_Mac)
    typedef std::pair<NSString*, NSEventModifierFlags> NativeKeyCode;
#elif defined(CS_Win)
    typedef System::Windows::Forms::Keys NativeKeyCode;
#endif
private:
    NativeKeyCode nativeKeyCode;
public:
    CSKeyCode() :
#if defined(CS_Mac)
        nativeKeyCode(std::make_pair(@"", 0)) {}
#elif defined(CS_Win)
        nativeKeyCode(System::Windows::Forms::Keys::None) {}
#endif

    CSKeyCode(std::string keyString, bool cmd, bool mod, bool shift) :
#if defined(CS_Mac)
        nativeKeyCode(std::make_pair([[NSString alloc] initWithStdString:keyString],
                                     (cmd * NSEventModifierFlagCommand) ||
                                     (mod * NSEventModifierFlagOption) ||
                                     (shift * NSEventModifierFlagShift))) {}
#elif defined(CS_Win)
        nativeKeyCode((NativeKeyCode)System::Enum::Parse(NativeKeyCode::typeid, gcnew System::String(keyString.c_str()), true)) {
        if (cmd) {
            nativeKeyCode = nativeKeyCode | NativeKeyCode::Control;
        }
        if (mod) {
            nativeKeyCode = nativeKeyCode | NativeKeyCode::Alt;
        }
        if (shift) {
            nativeKeyCode = nativeKeyCode | NativeKeyCode::Shift;
        }
    }
#endif

    NativeKeyCode toNativeKeyCode() {
        return nativeKeyCode;
    }
    
private:
    CSKeyCode(NativeKeyCode k) : nativeKeyCode(k) {}
public:
    static CSKeyCode backspace() {
#if defined(CS_Mac)
        return CSKeyCode(std::make_pair([NSString stringWithFormat:@"%c" , NSBackspaceCharacter], 0));
#elif defined(CS_Win)
        return CSKeyCode(NativeKeyCode::Back | NativeKeyCode::Control);
#endif
    }
};

#endif /* CSKeyCode_hpp */
