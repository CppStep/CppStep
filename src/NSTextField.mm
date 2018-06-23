//
//  NSTextField.mm
//  VDJartnet
//
//  Created by Jonathan Tanner on 13/05/2018.
//  Copyright © 2018 Jonathan Tanner. All rights reserved.
//

#import "NSTextField.h"

@implementation CSTextFieldCallbacks {
    std::function<bool(std::string)> function;
}

- (id) initWithFunction:(std::function<bool(std::string)>)functionTMP {
    function = functionTMP;
}

- (BOOL)control:(NSControl*)control textShouldEndEditing:(NSText*)fieldEditor {
    function(std::string([fieldEditor cStringUsingEncoding: NSUTF8StringEncoding]));
}

@end

@implementation NSTextField (CSCallbacks)

- (void) setCallback:(std::function<bool(std::string)>)callback {
    [self setDelegate: [[CSTextFieldCallback alloc] initWithFunction: callback]];
}

@end
