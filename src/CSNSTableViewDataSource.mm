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

#ifndef CSNSTableViewDataSource_mm
#define CSNSTableViewDataSource_mm


@interface CSNSTableViewDataSource : NSTableView <NSTableViewDataSource> {
    CSTableViewDataSource* dataSource;
}

- (id) initWithDataSource:(CSTableViewDataSource*)dataSourceTMP {
    dataSource = dataSourceTMP
}

- (NSInteger) numberOfRowsInTableView:(NSTableView*)tableView {
    return @(dataSource->numberOfRows());
}

- (id) tableView:(NSTableView*)tableView
       objectValueForTableColumn:(NSTableColumn*)tableColumn
       row:(NSInteger)row {
    return @(dataSource->getStringValueInCell(CSTableColumn(tableColumn), (int)row).c_str());
}

- (void) tableView:(NSTableView*)tableView
         setObjectValue:(id)object
         forTableColumn:(NSTableColumn*)tableColumn
         row:(NSInteger)row {
    dataSource->setStringValueInCell(CSTableColumn(tableColumn), (int)row, std::string([object UTF8String]));
}

- (BOOL) tableView:(NSTableView*)tableView
         writeRowsWithIndexes:(NSIndexSet*)rowIndexes
         toPasteboard:(NSPasteboard*)pboard {
    if (dataSource->canDragFromRow(rowIndexes[0])) {
        [pboard declareTypes:[NSArray<NSString*>
                arrayWithObject:NSStringPboardType]
                owner:self];
        [pboard setString:dataSource->dragStringValueFromRow(rowIndexes[0])
                forType:NSStringPboardType];
        return YES;
    } else {
        return NO;
    }
}

- (NSDragOperation) tableView:(NSTableView*)tableView
                    validateDrop:(id<NSDraggingInfo>)info
                    proposedRow:(NSInteger)row
                    proposedDropOperation:(NSTableViewDropOperation)dropOperation {
    if (dataSource->canDropIntoRow(row)) {
        return NSDragOperationCopy;
    } else {
        return NSDragOperationNone;
    }
}

- (BOOL) tableView:(NSTableView*)tableView
         acceptDrop:(id<NSDraggingInfo>)info
         row:(NSInteger)row
         dropOperation:(NSTableViewDropOperation)dropOperation {
    dataSource->dropStringValueInRow(row, std::string([[[info draggingPasteboard] stringForType:NSStringPboardType] UTF8String]))
    return YES;
}

@end

#endif /* CSNSTableViewDataSource_mm */
