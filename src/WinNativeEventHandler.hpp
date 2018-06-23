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
#include <msclr\gcroot.h>
#include <msclr\marshal_cppstd.h>
#using <mscorlib.dll>

#include <functional>
#include <utility>
#include <initializer_list>
#include <iostream>

template <typename... Ts>
ref class PropertyNames {};

template <typename T>
ref class PropertyNames<T> {
public:
    PropertyNames(System::String^ name) : name(name), tail(gcnew PropertyNames<>) {}
    PropertyNames(System::String^ name, PropertyNames<>^ tail) : name(name), tail(tail) {}
    System::String^ name;
    PropertyNames<>^ tail;
};

template <typename T, typename... Ts>
ref class PropertyNames<T, Ts...> {
public:
    PropertyNames(System::String^ name, PropertyNames<Ts...>^ tail) : name(name), tail(tail) {}
    System::String^ name;
    PropertyNames<Ts...>^ tail;
};

template <typename R, typename Arg>
inline std::function<R()> bindFirst(std::function<R(Arg)> f, Arg arg) {
    return [=](){ return f(arg); };
}

template <typename R, typename Arg, typename... Args>
inline std::function<R(Args...)> bindFirst(std::function<R(Arg, Args...)> f, Arg arg) {
    return [=](Args... args){ return f(arg, args...); };
}

template <typename Arg>
inline Arg getNativePropertyOnObject(System::Object^ obj, System::String^ propertyName) {
    if (obj != nullptr) {
        System::Reflection::PropertyInfo^ property = obj->GetType()->GetProperty(propertyName);
        if (property != nullptr) {
            System::Object^ argMan = property->GetValue(obj, nullptr);
            System::IntPtr argPtr;
#define Marshal System::Runtime::InteropServices::Marshal
            System::IntPtr argPtr = Marshal::AllocHGlobal(Marshal::SizeOf(argMan));
            Marshal::StructureToPtr(argMan, argPtr, false);
            Arg* argNat = (Arg*)(argPtr.ToPointer());
            if (argNat != nullptr) {
                return *argNat;
            } else {
                std::cerr << "Could not generate native value" << std::endl;
                throw "Could not generate native value";
            }
#undef Marshal
        } else {
            std::cerr << "Property does not exist" << std::endl;
            throw "Property does not exist";
        }
    } else {
        std::cerr << "obj was null" << std::endl;
        throw "obj was null";
    }
}

template <>
inline std::string getNativePropertyOnObject<std::string>(System::Object^ obj, System::String^ propertyName) {
    if (obj != nullptr) {
        System::Reflection::PropertyInfo^ property = obj->GetType()->GetProperty(propertyName);
        if (property != nullptr) {
            System::Object^ argMan = property->GetValue(obj, nullptr);
            System::IntPtr argPtr;
#define Marshal System::Runtime::InteropServices::Marshal
            if (argMan->GetType() == System::String::typeid) {
                System::IntPtr argPtr = Marshal::StringToHGlobalAuto(dynamic_cast<System::String^>(argMan));
                wchar_t const* argChrPtr = (wchar_t*)(argPtr.ToPointer());
                std::wstring argWStr(argChrPtr);
                std::string argStr(argWStr.begin(), argWStr.end());
                return argStr;
            } else {
                std::cerr << "Property does not contain a System::String" << std::endl;
                throw "Property does not contain a System::String";
            }
#undef Marshal
        } else {
            std::cerr << "Property does not exist" << std::endl;
            throw "Property does not exist";
        }
    } else {
        std::cerr << "obj was null" << std::endl;
        throw "obj was null";
    }
}

template <typename R>
inline R callFunctionOnObject(std::function<R()> f, System::Object^ obj, PropertyNames<>^ properties) {
    return f();
}

template <typename R, typename Arg>
inline R callFunctionOnObject(std::function<R(Arg)> f, System::Object^ obj, PropertyNames<Arg>^ properties) {
    return f(getNativePropertyOnObject<Arg>(obj, properties->name));
}

template <typename R, typename Arg, typename... Args>
inline R callFunctionOnObject(std::function<R(Arg, Args...)> f, System::Object^ obj, PropertyNames<Arg, Args...>^ properties) {
    Arg arg = getNativePropertyOnObject<Arg>(obj, properties->name);
    return callFunctionOnObject<R, Args...>(bindFirst(f, arg), obj, properties->tail);
}

template <typename>
ref class WinNativeFunctionWrapper;

template <typename R>
ref class WinNativeFunctionWrapper<R()> {
public:
    WinNativeFunctionWrapper(std::function<R()> functionTMP) {
        function = new std::function<R()>(functionTMP);
    }

    inline void callFunction(System::Object^ sender, System::EventArgs^ e) {
        (*function)();
    }
private:
    std::function<R()> const* function;
};

template <typename R, typename... Args>
ref class WinNativeFunctionWrapper<R(Args...)> {
public:
    WinNativeFunctionWrapper(std::function<R(Args...)> functionTMP, PropertyNames<Args...>^ propertyNames)
        : propertyNames(propertyNames) {
        function = new std::function<R(Args...)>(functionTMP);
    }

    inline void callFunction(System::Object^ sender, System::EventArgs^ e) {
        callFunctionOnObject(*function, sender, propertyNames);
    }
private:
    const std::function<R(Args...)>* function;
    PropertyNames<Args...>^ propertyNames;
};

template <typename R>
System::EventHandler^ gcnew_WinNativeEventHandler(std::function<R()> function) {
    auto wrapper = gcnew WinNativeFunctionWrapper<R()>(function);
    return gcnew System::EventHandler(wrapper, &WinNativeFunctionWrapper<R()>::callFunction);
}

template <typename R, typename... Args>
System::EventHandler^ gcnew_WinNativeEventHandler(std::function<R(Args...)> function, PropertyNames<Args...>^ propertyNames) {
    auto wrapper = gcnew WinNativeFunctionWrapper<R(Args...)>(function, propertyNames);
    return gcnew System::EventHandler(wrapper, &WinNativeFunctionWrapper<R(Args...)>::callFunction);
}

#endif /* WinNativeEventHandler_hpp */
