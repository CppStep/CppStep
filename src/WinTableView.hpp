//
//  WinTableView.hpp
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

#ifndef WinTableView_hpp
#define WinTableView_hpp

#include "WinTableViewDataSource.hpp"
#include "CSRect.hpp"

#using <System.dll>
#using <System.Windows.Forms.dll>
// #using <mscorlib.dll>
#include <msclr\marshal_cppstd.h>

#include <iostream>

ref class WinTableView : public System::Windows::Forms::DataGridView {
public:
    WinTableView(CSRect rect);

    void setDataSource(CSTableViewDataSource* dataSourceTMP);

    void addColumn(std::string name);
    void setHeaderColumn(std::string name);

    void mouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
    void mouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
    void dragEnter(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e);
    void dragDrop(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e);
private:
    CSTableViewDataSource* dataSource;

    System::Windows::Forms::DataGridViewRow^ rowToDrag;
    System::Drawing::Rectangle dragBoxFromMouseDown; // A box around the initial click point
};

#endif /* WinTableView_hpp */
