//
//  CSDialog.cpp
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

#include "CSDialog.hpp"

int CSDialog::show(std::string title,
                   std::string message,
                   std::vector<std::string> buttons
                   ) {
#if defined(CS_Mac)
    NSAlert* alert = [[NSAlert alloc] init];
    [alert setMessageText:[[NSString alloc] initWithStdString:title]];
    [alert setInformativeText:[[NSString alloc] initWithStdString:message]];
    for (std::string button : buttons) {
        [alert addButtonWithTitle:[[NSString alloc] initWithStdString:button]];
    }
    switch ([alert runModal]) {
        case NSAlertFirstButtonReturn:
            return 0;
        case NSAlertSecondButtonReturn:
            return 1;
        case NSAlertThirdButtonReturn:
            return 2;
        default:
            return -1;
    }
#elif defined(CS_Win)
#endif
}
