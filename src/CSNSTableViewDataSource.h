//
//  CSNSTableViewDataSource.h
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

#ifndef CSNSTableViewDataSource_h
#define CSNSTableViewDataSource_h

#include "CSTableViewDataSource.hpp"
#import "NSString.h"
#import <AppKit/AppKit.h>

/** An NSTableViewDataSource wrapper for a CSTableViewDataSource */
@interface CSNSTableViewDataSource : NSObject <NSTableViewDataSource>

- (id)initWithDataSource:(CSTableViewDataSource*)dataSourceTMP; /**< Initialise a list of commands with the given instance of the plugin */

- (NSInteger)numberOfRowsInTableView:(NSTableView*)tableView; /**< The number of commands in the list */
- (id)tableView:(NSTableView*)tableView objectValueForTableColumn:(NSTableColumn*)tableColumn row:(NSInteger)row; /**< Get the value of the command in the given row */
- (void)tableView:(NSTableView*)tableView setObjectValue:(id)object forTableColumn:(NSTableColumn*)tableColumn row:(NSInteger)row; /**< Set the value of the command in the given row */

- (BOOL)tableView:(NSTableView*)tableView writeRowsWithIndexes:(NSIndexSet*)rowIndexes toPasteboard:(NSPasteboard*)pboard;
- (NSDragOperation)tableView:(NSTableView*)tableView validateDrop:(id<NSDraggingInfo>)info proposedRow:(NSInteger)row proposedDropOperation:(NSTableViewDropOperation)dropOperation;
- (BOOL)tableView:(NSTableView*)tableView acceptDrop:(id<NSDraggingInfo>)info row:(NSInteger)row dropOperation:(NSTableViewDropOperation)dropOperation;

@end

#endif /* CSNSTableViewDataSource_h */

