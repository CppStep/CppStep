//
//  NSWindow.mm
//  VDJartnet
//
//  Created by Jonathan Tanner on 13/05/2018.
//  Copyright © 2018 Jonathan Tanner. All rights reserved.
//

#import "NSWindow.h"

@implementation CSWindowCallbacks {
    std::function<void()> resizeFunction;
    std::function<bool()> closeFunction;
}

- (id) initWithResizeFunction:(std::function<void()>)resizeFunctionTMP closeFunction:(std::function<bool()>)closeFunctionTMP {
    if ( self = [super init] ) {
        resizeFunction = resizeFunctionTMP;
        closeFunction = closeFunctionTMP;
        return self;
    } else {
        return nil;
    }
}

- (void)windowDidResize:(NSNotification *)notification {
    resizeFunction();
}

- (BOOL)windowShouldClose:(NSWindow *)sender {
    return closeFunction();
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
                                    defer: YES
                 ] ) {
        [self setReleasedWhenClosed: NO];
        [self setTitle: @(title.c_str())];
        return self;
    } else {
        return nil;
    }
}

- (void) presentView:(CSView*)view menuBar:(CSMenuBar*)menuBar {
    [self setContentView:view->toNativeView()];
    [self setMenu:menuBar->toNativeMenu()];
}

- (CSWindowCallbacks*) setResizeCallback:(std::function<void()>)resizeCallback closeCallback:(std::function<bool()>)closeCallback {
    CSWindowCallbacks* delegate = [[CSWindowCallbacks alloc] initWithResizeFunction:resizeCallback closeFunction:closeCallback];
    [self setDelegate: delegate];
    return delegate;
}

@end

