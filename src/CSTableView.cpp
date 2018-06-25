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
    [nativeView setAllowsMultipleSelection:NO];
#elif defined(CS_Win)
    nativeView = gcnew WinTableView(rect);
#endif
}

void CSTableView::setDataSource(CSTableViewDataSource* dataSourceTMP) {
    dataSource = dataSourceTMP;
#if defined(CS_Mac)
    [nativeView setDataSource: [[CSNSTableViewDataSource alloc] initWithDataSource: dataSource]];
#elif defined(CS_Win)
    nativeView->setDataSource(dataSource);
#endif
}

void CSTableView::addColumn(std::string name) {
#if defined(CS_Mac)
    [nativeView addTableColumn: [[NSTableColumn alloc] initWithIdentifier: @(name.c_str())]];
#elif defined(CS_Win)
    nativeView->addColumn(name);
#endif
}

void CSTableView::setHeaderColumn(std::string name) {
#if defined(CS_Mac)
    [nativeView addTableColumn: [[NSTableColumn alloc] initWithIdentifier: @(name.c_str())]];
#elif defined(CS_Win)
    nativeView->setHeaderColumn(name);
#endif
}

int CSTableView::getSelectedRow() {
#if defined(CS_Mac)
    return (int)[nativeView selectedColumn];
#elif defined(CS_Win)
    if (nativeView->SelectedRows->Count > 0) {
        return nativeView->SelectedRows[0]->Index;
    } else {
        return -1;
    }
#endif
}

CSView::NativeView CSTableView::toNativeView() {
#if defined(CS_Mac)
    return this->nativeView;
#elif defined(CS_Win)
    return safe_cast<CSView::NativeView>(this->nativeView);
#endif
}
