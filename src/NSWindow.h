//
//  NSWindow.h
//  VDJartnet
//
//  Created by Jonathan Tanner on 13/05/2018.
//  Copyright © 2018 Jonathan Tanner. All rights reserved.
//

#include "CSView.hpp"
#include "CSRect.hpp"

#import <AppKit/AppKit.h>

#include <functional>
#include <string>

@interface CSWindowCallbacks (NSObject, NSWindowDelegate)

- (id) initWithFunction:(std::function<void()>)function; /**< Create a callback object with the given function */

- (void)windowDidResize:(NSNotification *)notification;

@end

@interface NSWindow (CSWindow)

/** Initialise an NSWindow with the given C++ style arguments */
- (id) initWithsize:(CSRect)rect
              title:(std::string)title
         isClosable:(bool)closable
        isResizable:(bool)resizable
;

/** Present the given CSView */
- (void) presentView:(CSView*)view;

/** Set the windowDidResize callback to the given function */
- (void) setCallback:(std::function<void()>)callback;

@end
