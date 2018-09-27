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
    nativeTableView = [[NSTableView alloc] initWithFrame:rect.toNativeRect()];
    [nativeTableView setAllowsMultipleSelection:NO];
    [nativeTableView setUsesAlternatingRowBackgroundColors:YES];
    
    [nativeTableView setDraggingSourceOperationMask:NSDragOperationCopy forLocal:YES];
    [nativeTableView setDraggingSourceOperationMask:NSDragOperationCopy forLocal:NO];
    [nativeTableView registerForDraggedTypes:@[NSPasteboardTypeString]];
    
    nativeView = [[NSScrollView alloc] initWithFrame:NSZeroRect];
    [nativeView setDocumentView:nativeTableView];
    [nativeView setHasVerticalScroller:YES];
#elif defined(CS_Win)
    nativeView = gcnew WinTableView(rect);
#endif
}

void CSTableView::setDataSource(CSTableViewDataSource* dataSourceTMP) {
    dataSource = dataSourceTMP;
#if defined(CS_Mac)
    nativeDataSource = [[CSNSTableViewDataSource alloc] initWithDataSource: dataSource];
    [nativeTableView setDataSource: nativeDataSource];
    //[nativeTableView setDelegate: nativeDataSource];
#elif defined(CS_Win)
    nativeView->setDataSource(dataSource);
#endif
}

void CSTableView::setContextMenu(CSContextMenu* contextMenu) {
#if defined(CS_Mac)
    //TODO: Add Context Menu
#elif defined(CS_Win)
    nativeView->ContextMenuStrip = contextMenu->toNativeMenu();
#endif
}

void CSTableView::addColumn(std::string name) {
#if defined(CS_Mac)
    NSTableColumn* column = [[NSTableColumn alloc] initWithIdentifier: [[NSString alloc] initWithStdString:name]];
    [column setTitle:[[NSString alloc] initWithStdString:name]];
    [nativeTableView addTableColumn: column];
#elif defined(CS_Win)
    nativeView->addColumn(name);
#endif
}

void CSTableView::setHeaderColumn(std::string name) {
#if defined(CS_Mac)
    NSTableColumn* column = [[NSTableColumn alloc] initWithIdentifier: [[NSString alloc] initWithStdString:name]];
    [column setTitle:[[NSString alloc] initWithStdString:name]];
    [nativeTableView addTableColumn: column];
    [nativeTableView moveColumn:[nativeTableView numberOfColumns] - 1 toColumn:0];
#elif defined(CS_Win)
    nativeView->setHeaderColumn(name);
#endif
}

int CSTableView::getSelectedRow() {
#if defined(CS_Mac)
    return (int)[nativeTableView selectedColumn];
#elif defined(CS_Win)
    if (nativeView->SelectedRows->Count > 0) {
        return nativeView->SelectedRows[0]->Index;
    } else {
        return -1;
    }
#endif
}

void CSTableView::reload() {
#if defined(CS_Mac)
    [nativeTableView reloadData];
#elif defined(CS_Win)
    nativeView->Refresh();
#endif

}

CSView::NativeView CSTableView::toNativeView() {
#if defined(CS_Mac)
    return this->nativeView;
#elif defined(CS_Win)
    return safe_cast<CSView::NativeView>(this->nativeView);
#endif
}
