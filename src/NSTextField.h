//
//  NSTextField.h
//  VDJartnet
//
//  Created by Jonathan Tanner on 13/05/2018.
//  Copyright © 2018 Jonathan Tanner. All rights reserved.
//

#import "NSString.h"

#import <AppKit/AppKit.h>

#include <functional>
#include <string>

@interface CSTextFieldCallback : NSObject <NSTextFieldDelegate>

- (id) initWithFunction:(std::function<bool(std::string)>)function; /**< Create a callback object with the given function */

- (BOOL)control:(NSControl*)control textShouldEndEditing:(NSText*)fieldEditor; /**< The text has been edited */

@end

@interface NSTextField (CSCallback)

- (CSTextFieldCallback*) setCallback:(std::function<bool(std::string)>)callback  __attribute__((warn_unused_result));

@end
