//
//  WinTableView.cpp
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

#include "WinTableView.hpp"
#include <iostream>

WinTableView::WinTableView(CSRect rect) {
    this->AutoGenerateColumns = false;
    this->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
    this->RowHeadersVisible = true;
    this->AllowDrop = true;
    this->AllowUserToAddRows = false;
    this->ClipboardCopyMode = System::Windows::Forms::DataGridViewClipboardCopyMode::EnableWithoutHeaderText;
    this->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
    this->Location = rect.origin.toNativePoint();
    this->Size = rect.size.toNativeSize();

    this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &WinTableView::mouseDown);
    this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &WinTableView::mouseMove);
    this->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &WinTableView::dragEnter);
    this->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &WinTableView::dragDrop);
}

void WinTableView::setDataSource(CSTableViewDataSource* dataSourceTMP) {
    dataSource = dataSourceTMP;
    this->DataSource = gcnew WinTableViewDataSource(dataSource);
}

void WinTableView::addColumn(std::string name) {
    System::Windows::Forms::DataGridViewTextBoxColumn^ column = gcnew System::Windows::Forms::DataGridViewTextBoxColumn();
    column->Name = gcnew System::String(name.c_str());
    column->DataPropertyName = gcnew System::String(name.c_str());
    column->ReadOnly = dataSource->isReadOnly(name);
    this->Columns->Add(column);
}

void WinTableView::setHeaderColumn(std::string name) {
    this->Refresh();
    for each (System::Windows::Forms::DataGridViewRow^ row in this->Rows) {
        row->HeaderCell->Value = gcnew System::String(dataSource->getStringValueInCell(name, row->Index).c_str());
    }
    this->AutoResizeRowHeadersWidth(System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders);
}

void WinTableView::mouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
    System::Windows::Forms::DataGridView::HitTestInfo^ hit = this->HitTest(e->X, e->Y);

    if (hit->Type == System::Windows::Forms::DataGridViewHitTestType::Cell) {
        rowToDrag = this->Rows[hit->RowIndex];
        if (dataSource->canDragFromRow(rowToDrag->Index)) {
            System::Drawing::Size dragSize = System::Windows::Forms::SystemInformation::DragSize;
            dragBoxFromMouseDown = System::Drawing::Rectangle(System::Drawing::Point(e->X - (dragSize.Width / 2), e->Y - (dragSize.Height / 2)), dragSize);
            return;
        }
    }
    rowToDrag = nullptr;
    dragBoxFromMouseDown = System::Drawing::Rectangle::Empty;
}

void WinTableView::mouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
    if ((e->Button & System::Windows::Forms::MouseButtons::Left) == System::Windows::Forms::MouseButtons::Left) {
        if (dragBoxFromMouseDown != System::Drawing::Rectangle::Empty && !dragBoxFromMouseDown.Contains(e->X, e->Y)) {
            if (rowToDrag != nullptr) {
                this->DoDragDrop(gcnew System::String(dataSource->dragStringValueFromRow(rowToDrag->Index).c_str()), System::Windows::Forms::DragDropEffects::Copy);
            }
        }
    }
}

void WinTableView::dragEnter(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e) {
    if (e->Data->GetDataPresent(System::String::typeid)) {
        e->Effect = System::Windows::Forms::DragDropEffects::Copy;
    }
}

void WinTableView::dragDrop(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e) {
    System::Drawing::Point coords = this->PointToClient(System::Drawing::Point(e->X, e->Y));
    System::Windows::Forms::DataGridView::HitTestInfo^ hit = this->HitTest(coords.X, coords.Y);
    if (hit->Type == System::Windows::Forms::DataGridViewHitTestType::Cell) {
        if (e->Data->GetDataPresent(System::String::typeid)) {
            if (e->Effect == System::Windows::Forms::DragDropEffects::Copy) {
                if (dataSource->canDropIntoRow(hit->RowIndex)) {
                    dataSource->dropStringValueInRow(hit->RowIndex, msclr::interop::marshal_as<std::string>(dynamic_cast<System::String^>(e->Data->GetData(System::String::typeid))));
                    this->Refresh();
                }
            }
        }
    }
}
