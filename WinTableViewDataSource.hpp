//
//  WinTableViewDataSource.hpp
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

#ifndef WinTableViewDataSource_hpp
#define WinTableViewDataSource_hpp

#include "CSTableViewDataSource.hpp"

#using <System.dll>
#using <System.Windows.Forms.dll>
// #using <mscorlib.dll>
#include <msclr\marshal_cppstd.h>

#include <iostream>

ref class WinTableRowString : public System::Object, public System::ComponentModel::ICustomTypeDescriptor {
public:
    WinTableRowString(CSTableViewDataSource* dataSource, int row) : dataSource(dataSource), row(row) {}

    int getRow() {
        return row;
    }

    virtual System::ComponentModel::AttributeCollection^ GetAttributes() {
        return System::ComponentModel::TypeDescriptor::GetAttributes(this, true);
    }
    virtual System::String^ GetClassName() {
        return System::ComponentModel::TypeDescriptor::GetClassName(this, true) + System::Convert::ToString(row);
    }
    virtual System::String^ GetComponentName() {
        return System::ComponentModel::TypeDescriptor::GetComponentName(this, true) + System::Convert::ToString(row);
    }
    virtual System::ComponentModel::TypeConverter^ GetConverter() {
        return System::ComponentModel::TypeDescriptor::GetConverter(this, true);
    }
    virtual System::ComponentModel::EventDescriptor^ GetDefaultEvent() {
        return System::ComponentModel::TypeDescriptor::GetDefaultEvent(this, true);
    }
    virtual System::ComponentModel::PropertyDescriptor^ GetDefaultProperty() {
        return System::ComponentModel::TypeDescriptor::GetDefaultProperty(this, true);
    }
    virtual System::Object^ GetEditor(System::Type^ editorBaseType) {
        return System::ComponentModel::TypeDescriptor::GetEditor(this, editorBaseType, true);
    }
    virtual System::ComponentModel::EventDescriptorCollection^ GetEvents() {
        return System::ComponentModel::TypeDescriptor::GetEvents(this, true);
    }
    virtual System::ComponentModel::EventDescriptorCollection^ GetEvents(array<System::Attribute^>^ attributes) {
        return System::ComponentModel::TypeDescriptor::GetEvents(this, attributes, true);
    }
    virtual System::Object^ GetPropertyOwner(System::ComponentModel::PropertyDescriptor^ property) {
        return this;
    }
    virtual System::ComponentModel::PropertyDescriptorCollection^ GetProperties() {
        return this->GetProperties(nullptr);
    }
    virtual System::ComponentModel::PropertyDescriptorCollection^ GetProperties(array<System::Attribute^>^ attributes);
private:
    CSTableViewDataSource* dataSource;
    int row;
};

ref class WinTableCellDescriptor : public System::ComponentModel::PropertyDescriptor {
public:
    WinTableCellDescriptor(CSTableViewDataSource* dataSource, System::String^ col) : System::ComponentModel::PropertyDescriptor(col, nullptr),
                                                                                          dataSource(dataSource),
                                                                                          col(col) {}
    property bool IsReadOnly {
        virtual bool get() override {
            return dataSource->isReadOnly(msclr::interop::marshal_as<std::string>(%*col));
        }
    }
    virtual void ResetValue(System::Object^ component) override {
        this->SetValue(component, "");
    }
    virtual bool CanResetValue(System::Object^ component) override {
        return true;
    }
    virtual bool ShouldSerializeValue(System::Object^ component) override {
        return true;
    }
    property System::Type^ ComponentType {
        virtual System::Type^ get() override {
            return WinTableRowString::typeid;
        }
    }
    property System::Type^ PropertyType {
        virtual System::Type^ get() override {
            return System::String::typeid;
        }
    }
    virtual System::Object^ GetValue(System::Object^ component) override {
        return gcnew System::String(dataSource->getStringValueInCell(msclr::interop::marshal_as<std::string>(%*col), safe_cast<WinTableRowString^>(component)->getRow()).c_str());
    }
    virtual void SetValue(System::Object^ component, System::Object^ value) override {
       dataSource->setStringValueInCell(msclr::interop::marshal_as<std::string>(%*col),
                                        safe_cast<WinTableRowString^>(component)->getRow(),
                                        msclr::interop::marshal_as<std::string>(safe_cast<System::String^>(value)));
       //OnValueChanged(component, EventArgs::Empty);
    }
private:
    CSTableViewDataSource* dataSource;
    System::String^ col;
};

ref class WinTableViewDataSource : public System::Windows::Forms::BindingSource {
public:
    WinTableViewDataSource(CSTableViewDataSource* dataSource) : System::Windows::Forms::BindingSource(), dataSource(dataSource) {
        refresh();
    }
    System::Collections::Generic::List<WinTableRowString^>^ getList() {
        auto list = gcnew System::Collections::Generic::List<WinTableRowString^>();
        for (int row = 0; row < dataSource->numberOfRows(); row++) {
            list->Add(gcnew WinTableRowString(dataSource, row));
        }
        return list;
    }
    void refresh() {
        this->DataSource = getList();
    }
private:
    CSTableViewDataSource* dataSource;
};

#endif /* WinTableViewDataSource_hpp */
