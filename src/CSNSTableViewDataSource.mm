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

@interface EmptyDelegate : NSObject <NSTableViewDelegate>
@end
@implementation EmptyDelegate
@end

@implementation CSNSFormatter
- (NSString*) stringForObjectValue:(id)obj {
    return @"not editing";
    NSPair<NSString*, NSString*>* pair = obj;
    return [pair first];
}
- (NSString*) editingStringForObjectValue:(id)obj {
    return @"editing";
    NSPair<NSString*, NSString*>* pair = obj;
    return [pair second];
}
@end

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

- (BOOL)tableView:(NSTableView *)tableView shouldEditTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    return !dataSource->isReadOnly([[tableColumn identifier] stdString]);
}

- (NSCell*) tableView:(NSTableView *)tableView dataCellForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    NSCell* cell = [[[EmptyDelegate alloc] init] tableView:tableView dataCellForTableColumn:tableColumn row: row+42];
    [cell setFormatter:[[CSNSFormatter alloc] init]];
}

- (NSInteger) numberOfRowsInTableView:(NSTableView*)tableView {
    return (NSInteger)dataSource->numberOfRows();
}

- (id) tableView:(NSTableView*)tableView
       objectValueForTableColumn:(NSTableColumn*)tableColumn
       row:(NSInteger)rowNS {
    std::string col = [[tableColumn identifier] stdString];
    std::size_t row = (std::size_t)rowNS;
    return @"test";/*[[NSPair alloc] initWithFirst: [[NSString alloc] initWithStdString: dataSource->getStringValueInCell(col, row, false)]
                                  second: [[NSString alloc] initWithStdString: dataSource->getStringValueInCell(col, row, true)]
            ];*/
}

- (void) tableView:(NSTableView*)tableView
         setObjectValue:(id)object
         forTableColumn:(NSTableColumn*)tableColumn
         row:(NSInteger)row {
    dataSource->setStringValueInCell([[tableColumn identifier] stdString], (std::size_t)row, [object stdString]);
}

- (BOOL) tableView:(NSTableView*)tableView
         writeRowsWithIndexes:(NSIndexSet*)rowIndexes
         toPasteboard:(NSPasteboard*)pboard {
    std::size_t row = (std::size_t)[rowIndexes firstIndex];
    if (dataSource->canDragFromRow(row)) {
        [pboard declareTypes:@[NSPasteboardTypeString]
                owner:nil];
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
    switch (dropOperation) {
        case NSTableViewDropOn:
            if (dataSource->canDropIntoRow((std::size_t)row)) {
                return NSDragOperationCopy;
            } else {
                return NSDragOperationNone;
            }
        case NSTableViewDropAbove:
            return NSDragOperationNone;
    }
}

- (BOOL) tableView:(NSTableView*)tableView
         acceptDrop:(id<NSDraggingInfo>)info
         row:(NSInteger)row
         dropOperation:(NSTableViewDropOperation)dropOperation {
    switch (dropOperation) {
        case NSTableViewDropOn:
            dataSource->dropStringValueInRow((std::size_t)row, [[[info draggingPasteboard] stringForType:NSPasteboardTypeString] stdString]);
            return YES;
        case NSTableViewDropAbove:
            return NO;
    }
}

@end
