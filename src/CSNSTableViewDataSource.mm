//
//  CSNSTableViewDataSource.mm
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

#import "CSNSTableViewDataSource.h"

@implementation CSNSTableViewDataSource {
    CSTableViewDataSource* dataSource;
}

- (id) initWithDataSource:(CSTableViewDataSource*)dataSourceTMP {
    if (self = [self init]) {
        dataSource = dataSourceTMP;
        return self;
    } else {
        return nil;
    }
}

- (NSInteger) numberOfRowsInTableView:(NSTableView*)tableView {
    return (NSInteger)dataSource->numberOfRows();
}

- (id) tableView:(NSTableView*)tableView
       objectValueForTableColumn:(NSTableColumn*)tableColumn
       row:(NSInteger)row {
    return @(dataSource->getStringValueInCell([[tableColumn identifier] stdString], (int)row).c_str());
}

- (void) tableView:(NSTableView*)tableView
         setObjectValue:(id)object
         forTableColumn:(NSTableColumn*)tableColumn
         row:(NSInteger)row {
    dataSource->setStringValueInCell([[tableColumn identifier] stdString], (int)row, [object stdString]);
}

- (BOOL) tableView:(NSTableView*)tableView
         writeRowsWithIndexes:(NSIndexSet*)rowIndexes
         toPasteboard:(NSPasteboard*)pboard {
    int row = (int)[rowIndexes firstIndex];
    if (dataSource->canDragFromRow(row)) {
        [pboard declareTypes:[NSArray<NSString*>
                arrayWithObject:NSPasteboardTypeString]
                owner:self];
        [pboard setString:[[NSString alloc] initWithStdString:dataSource->dragStringValueFromRow(row)]
                forType:NSPasteboardTypeString];
        return YES;
    } else {
        return NO;
    }
}

- (NSDragOperation) tableView:(NSTableView*)tableView
                    validateDrop:(id<NSDraggingInfo>)info
                    proposedRow:(NSInteger)row
                    proposedDropOperation:(NSTableViewDropOperation)dropOperation {
    if (dataSource->canDropIntoRow((int)row)) {
        return NSDragOperationCopy;
    } else {
        return NSDragOperationNone;
    }
}

- (BOOL) tableView:(NSTableView*)tableView
         acceptDrop:(id<NSDraggingInfo>)info
         row:(NSInteger)row
         dropOperation:(NSTableViewDropOperation)dropOperation {
    dataSource->dropStringValueInRow((int)row, [[[info draggingPasteboard] stringForType:NSPasteboardTypeString] stdString]);
    return YES;
}

@end
