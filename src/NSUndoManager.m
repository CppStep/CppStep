//
//  NSUndoManager.m
//  VDJartnet
//
//  Created by Jonathan Tanner on 19/10/2018.
//  Copyright © 2018 Jonathan Tanner. All rights reserved.
//

#import "NSUndoManager.h"

@implementation NSUndoManager (CSUndoManager)

- (BOOL)validateMenuItem:(NSMenuItem *)menuItem {
    if ([menuItem action] == @selector(undo)) {
        return [self canUndo];
    } else if ([menuItem action] == @selector(redo)) {
        return [self canRedo];
    } else {
        return YES;
    }
}

@end
