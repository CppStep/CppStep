//
//  CSClipboard.cpp
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

#include "CSClipboard.hpp"

void CSClipboard::clear() {
#if defined(CS_Mac)
    [[NSPasteboard generalPasteboard] clearContents];
#elif defined(CS_Win)
    System::Windows::Forms::Clipboard::Clear();
#endif
}

std::string CSClipboard::getStringValue() {
#if defined(CS_Mac)
    return std::string([[[NSPasteboard generalPasteboard] stringForType:NSPasteboardTypeString] UTF8String]);
#elif defined(CS_Win)
    return msclr::interop::marshal_as<std::string>(System::Windows::Forms::Clipboard::GetText());
#endif
}

void CSClipboard::setStringValue(std::string value) {
#if defined(CS_Mac)
    [[NSPasteboard generalPasteboard] declareTypes:[NSArray<NSString*> arrayWithObject:NSPasteboardTypeString] owner:nil];
    [[NSPasteboard generalPasteboard] setString:@(value.c_str()) forType:NSPasteboardTypeString];
#elif defined(CS_Win)
    System::Windows::Forms::Clipboard::SetText(gcnew System::String(value.c_str()));
#endif
}
