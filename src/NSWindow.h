//
//  NSWindow.h
//  VDJartnet
//
//  Created by Jonathan Tanner on 13/05/2018.
//  Copyright © 2018 Jonathan Tanner. All rights reserved.
//

#include "CSView.hpp"
#include "CSRect.hpp"
#include "CSMenu.hpp"

#import <AppKit/AppKit.h>

#include <functional>
#include <string>

@interface CSWindowCallbacks : NSObject <NSWindowDelegate>

- (id) initWithResizeFunction:(std::function<void()>)resizeFunction closeFunction:(std::function<bool()>)closeFunction; /**< Create a callback object with the given function */

- (void)windowDidResize:(NSNotification *)notification;

- (BOOL)windowShouldClose:(NSWindow *)sender;

@end

@interface NSWindow (CSWindow)

/** Initialise an NSWindow with the given C++ style arguments */
- (id) initWithsize:(CSRect)rect
              title:(std::string)title
         isClosable:(bool)closable
        isResizable:(bool)resizable
;

/** Present the given CSView */
- (void) presentView:(CSView*)view menuBar:(CSMenuBar*)menuBar;

/** Set the windowDidResize callback to the given function */
- (CSWindowCallbacks*) setResizeCallback:(std::function<void()>)resizeCallback closeCallback:(std::function<bool()>)closeCallback  __attribute__((warn_unused_result));

@end

