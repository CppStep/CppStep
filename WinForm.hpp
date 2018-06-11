//
//  WinForm.hpp
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

#ifndef WinForm_hpp
#define WinForm_hpp

#include "CSView.hpp"
#include "CSRect.hpp"

#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

#include <string>

/** A C++ compatible subclass of a Windows Form object */
ref class WinForm : public System::Windows::Forms::Form {
public:
    WinForm(CSRect rect,
            std::string title,
            bool closable,
            bool resizable
            );

    void presentView(CSView* view);

private:
};

#endif /* WinForm_hpp */
