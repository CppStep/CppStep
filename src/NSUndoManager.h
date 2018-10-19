//
//  NSUndoManager.h
//  VDJartnet
//
//  Created by Jonathan Tanner on 19/10/2018.
//  Copyright © 2018 Jonathan Tanner. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface NSUndoManager (CSUndoManager)

- (BOOL)validateMenuItem:(NSMenuItem *)menuItem;

@end
