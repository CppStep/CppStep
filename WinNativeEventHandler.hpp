//
//  WinNativeEventHandler.hpp
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

#ifndef WinNativeEventHandler_hpp
#define WinNativeEventHandler_hpp

#include "CSView.hpp"
#include "CSRect.hpp"

#using <System.dll>

#include <functional>
#include <iostream>

/** A C++ compatible subclass of an EventHandler object */
ref class WinNativeFunctionWrapper {
public:
    WinNativeFunctionWrapper(std::function<void()> function) : WinNativeFunctionWrapper(&function) {}
    WinNativeFunctionWrapper(std::function<void()>* functionTMP) {
        function = new std::function<void()>(*functionTMP);
    }

    void callFunction(System::Object^ sender, System::EventArgs^ e) {
        (*function)();
    }
private:
    std::function<void()>* function;
};

// #define gcnew_WinNativeEventHandler(function) do { \
//     WinNativeFunctionWrapper^ wrapper = gcnew WinNativeFunctionWrapper(function); \
//     return gcnew System::EventHandler(wrapper, &WinNativeFunctionWrapper::callFunction); \
// } while (0)

#endif /* WinNativeEventHandler_hpp */
