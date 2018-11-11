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

#include "CSApp.hpp"

#if defined(CS_Mac)
#import <AppKit/AppKit.h>
#include <CoreServices/CoreServices.h>
#elif defined(CS_Win)
#include <msclr\gcroot.h>
#using <System.Windows.Forms.dll>
#endif

void CSApp::Init() {
#if defined(CS_Mac)
#elif defined(CS_Win)
    //TODO: Check if these are required as they were in the Mac section
    // I don't think that they are
    //ProcessSerialNumber psn = { 0, kCurrentProcess };
    //TransformProcessType( &psn, kProcessTransformToForegroundApplication );
#endif
}
/** Enter the main runloop */
void CSApp::Run(bool isMain) {
#if defined(CS_Mac)
    if (isMain) {
        [[NSApplication sharedApplication] run];
    }
    [[NSApplication sharedApplication] setActivationPolicy:NSApplicationActivationPolicyRegular];//Accessory];
    [[NSApplication sharedApplication] activateIgnoringOtherApps:YES];
#elif defined(CS_Win)
    if (isMain) {
        System::Windows::Forms::Application::Run();
    }
#endif
}
