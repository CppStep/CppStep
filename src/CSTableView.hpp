//
//  CSTableView.hpp
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

#ifndef CSTableView_hpp
#define CSTableView_hpp

#include "CSCore.hpp"
#include "CSView.hpp"
#include "CSRect.hpp"

#if defined(CS_Mac)
#include "CSNSTableViewDataSource.h"
#import <AppKit/AppKit.h>
#elif defined(CS_Win)
#include "WinTableViewDataSource.hpp"
#include "WinTableView.hpp"
#using <System.dll>
#using <System.Windows.Forms.dll>
#include <msclr\gcroot.h>
#include <msclr\marshal_cppstd.h>
#endif

#include <string>
#include <iostream>

#include "CSTableViewDataSource.hpp"

/** A table */
class CSTableView : public CSView {
public:
    /** Create a CSTableView with zero size */
    CSTableView() : CSTableView(CSRect()) {}
    /** Create a CSTableView
      * @param rect The frame for the view
      */
    CSTableView(CSRect rect);

    /** Set the Data Source
      * @param dataSource The Data Source
      */
    void setDataSource(CSTableViewDataSource* dataSourceTMP);

    /** Add a column
      * @param name The name of the column
      */
    void addColumn(std::string name);

    /** Set the given column in the Data Source to be the header
      * @param name The name of the column
      */
    void setHeaderColumn(std::string name);

    /** Get the index of the currently selected row
      * @return The index of the currently selected row or -1 if no rows are selected
      */
    int getSelectedRow();

    /** Reload the data from the data source
      */
    void reload();

#if defined(CS_Mac)
    typedef NSTableView* NativeView;
#elif defined(CS_Win)
    typedef msclr::gcroot<WinTableView^> NativeView;
#endif
    virtual CSView::NativeView toNativeView();
private:
    NativeView nativeView;

    CSTableViewDataSource* dataSource;
};

#endif /* CSTableView_hpp */
