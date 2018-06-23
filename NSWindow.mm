//
//  NSWindow.mm
//  VDJartnet
//
//  Created by Jonathan Tanner on 13/05/2018.
//  Copyright © 2018 Jonathan Tanner. All rights reserved.
//

#import "NSWindow.h"

@implementation CSWindowCallbacks {
    std::function<void()> function;
}

- (id) initWithFunction:(std::function<void()>)functionTMP {
    if ( self = [super init] ) {
        function = functionTMP;
        return self;
    } else {
        return nil;
    }
}

- (void)windowDidResize:(NSNotification *)notification {
    function();
}

@end

@implementation NSWindow (CSWindow)

- (id) initWithsize:(CSRect)rect
              title:(std::string)title
         isClosable:(bool)closable
        isResizable:(bool)resizable
{
    if ( self = [self initWithContentRect: rect.toNativeRect()
                                styleMask: NSWindowStyleMaskTitled// * !title.empty())
                                         | (NSWindowStyleMaskClosable * closable)
                                         | (NSWindowStyleMaskResizable * resizable)
                                         | NSWindowStyleMaskMiniaturizable
                                  backing: NSBackingStoreBuffered
                                    defer: NO
                 ] ) {
        [self setReleasedWhenClosed: NO];
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

- (void) setCallback:(std::function<void()>)callback {
    [self setDelegate: [[CSWindowCallbacks alloc] initWithFunction: callback]];
}

@end
