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
    if ( self = [super initWithContentRect: rect.toNativeRect()
                                 styleMask: (NSWindowStyleMaskTitled * !title.isEmpty)
                                          | (NSWindowStyleMaskClosable * closable)
                                          | (NSWindowStyleMaskResizable * resizable)
                                          | NSWindowStyleMaskMiniaturizable
                              backingStore: NSBackingStoreBuffered
                                     defer: NO
                ] ) {
        [self setReleasedWhenClosed: NO];
        [self setContentView: view.toNativeView()];
        [self setTitle: @(title.c_str())];
        [self makeKeyAndOrderFront: self];
        return self;
    } else {
        return nil;
    }
}

- (void) presentView:(CSView*)view {
    [self setContentView: view->toNativeView()];
}

@end
