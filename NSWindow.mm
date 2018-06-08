//
//  NSWindow.mm
//  VDJartnet
//
//  Created by Jonathan Tanner on 13/05/2018.
//  Copyright © 2018 Jonathan Tanner. All rights reserved.
//

#import "NSWindow.h"

@implementation NSWindow (CSView)

- (id) initWithCSView:(CSView*)view
                 size:(CSRect)rect
                title:(std::string)title 
           isClosable:(bool)closable 
          isResizable:(bool)resizable
{
    if ( self = [self initWithContentRect: rect.toNativeRect()
                                styleMask: (NSWindowStyleMaskTitled * !title.empty())
                                         | (NSWindowStyleMaskClosable * closable)
                                         | (NSWindowStyleMaskResizable * resizable)
                                         | NSWindowStyleMaskMiniaturizable
                                  backing: NSBackingStoreBuffered
                                    defer: NO
                 ] ) {
        [self setReleasedWhenClosed: NO];
        [self setContentView: view->toNativeView()];
        [self setTitle: @(title.c_str())];
        [self makeKeyAndOrderFront: nil];
        return self;
    } else {
        return nil;
    }
}

- (void) presentView:(CSView*)view {
    [self setContentView: view->toNativeView()];
}

@end
