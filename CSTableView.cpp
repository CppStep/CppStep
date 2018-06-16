//
//  CSTableView.cpp
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

#include "CSTableView.hpp"

CSTableView::CSTableView(CSRect rect) {
#if defined(CS_Mac)
    nativeView = [[NSTableView alloc] initWithFrame:rect.toNativeRect()];
#elif defined(CS_Win)
    nativeView = gcnew System::Windows::Forms::DataGridView();
    nativeView->AutoGenerateColumns = false;
    nativeView->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
    nativeView->Location = rect.origin.toNativePoint();
    nativeView->Size = rect.size.toNativeSize();
#endif
}

ref class Row : public System::Object {
public:
    property System::String^ Column {
        System::String^ get() {
            return "Hello World";
        }
    }
};

void CSTableView::setDataSource(CSTableViewDataSource* dataSourceTMP) {
    dataSource = dataSourceTMP;
#if defined(CS_Mac)
    [nativeView setDataSource: [[CSNSTableViewDataSource alloc] initWithDataSource: dataSource]];
#elif defined(CS_Win)
    nativeView->DataSource = gcnew WinTableViewDataSource(dataSource);
#endif
}

void CSTableView::addColumn(std::string name) {
    columns.push_back(CSTableColumn(columns.size(), name));
#if defined(CS_Mac)
    [nativeView addColumn: [[NSTableColumn alloc] initWithName: @(name)]];
#elif defined(CS_Win)
    System::Windows::Forms::DataGridViewTextBoxColumn^ column = gcnew System::Windows::Forms::DataGridViewTextBoxColumn();
    column->Name = gcnew System::String(name.c_str());
    column->DataPropertyName = gcnew System::String(name.c_str());
    column->ReadOnly = dataSource->isReadOnly();
    nativeView->Columns->Add(column);
#endif
}

CSView::NativeView CSTableView::toNativeView() {
#if defined(CS_Mac)
    return this->nativeView;
#elif defined(CS_Win)
    return safe_cast<CSView::NativeView>(this->nativeView);
#endif
}
