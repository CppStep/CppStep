//
//  NSTextField.h
//  VDJartnet
//
//  Created by Jonathan Tanner on 13/05/2018.
//  Copyright © 2018 Jonathan Tanner. All rights reserved.
//

#import <AppKit/AppKit.h>

#include <function>
#include <string>

@interface CSCallback (NSObject, NSTextFieldDelegate)

- (id) initWithFunction:(std::function<void(std::string)>)function; /**< Create a callbacks object with the given function */

- (BOOL)control:(NSControl*)control textShouldEndEditing:(NSText*)fieldEditor; /**< The text has been edited */

@end

@interface NSTextField (CSCallbacks)

- (void) setCallback:(std::function<void(std::string)>)callback;

@end
