//
//  WinTableViewDataSource.cpp
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

#include "WinTableViewDataSource.hpp"
#include <iostream>

System::ComponentModel::PropertyDescriptorCollection^ WinTableRowString/*TypeDescriptor*/::GetProperties(array<System::Attribute^>^ attributes) {
    System::ComponentModel::PropertyDescriptorCollection^ nonDynamicProperties;
    if (attributes == nullptr) {
        nonDynamicProperties = System::ComponentModel::TypeDescriptor::GetProperties(this, true);
    } else {
        nonDynamicProperties = System::ComponentModel::TypeDescriptor::GetProperties(this, attributes, true);
    }
    auto properties = gcnew array<System::ComponentModel::PropertyDescriptor^>(nonDynamicProperties->Count + dataSource->numberOfColumns());
    nonDynamicProperties->CopyTo(properties, 0);
    for (int i = 0; i < dataSource->numberOfColumns(); i++) {
        properties[nonDynamicProperties->Count + i] =
            gcnew WinTableCellDescriptor(dataSource,
                                         gcnew System::String(dataSource->getColumnName(i).c_str()));
    }
    return gcnew System::ComponentModel::PropertyDescriptorCollection(properties);
}
