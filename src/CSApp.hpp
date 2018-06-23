//
//  CSApp.hpp
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

#ifndef CSApp_hpp
#define CSApp_hpp

#include "CSCore.hpp"

#if defined(CS_Mac)
#import <AppKit/AppKit.h>
#include <CoreServices/CoreServices.h>
#elif defined(CS_Win)
#include <msclr\gcroot.h>
#endif

namespace CSApp {
    /** Initialise the Application */
    void Init() {
#if defined(CS_Mac)
        ProcessSerialNumber psn = { 0, kCurrentProcess };
        TransformProcessType( &psn, kProcessTransformToForegroundApplication );
#elif defined(CS_Win)
#endif
    }

    /** Begin the main runloop */
    void Run() {
#if defined(CS_Mac)
        [[NSApplication sharedApplication] run];
        [[NSApplication sharedApplication] setActivationPolicy:NSApplicationActivationPolicyRegular];//Accessory];
        [[NSApplication sharedApplication] activateIgnoringOtherApps:YES];
#elif defined(CS_Win)
        System::Windows::Forms::Application::Run();
#endif
    }
}

#endif /* CSApp_hpp */
