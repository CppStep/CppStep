//
//  NSTextField.mm
//  VDJartnet
//
//  Created by Jonathan Tanner on 13/05/2018.
//  Copyright © 2018 Jonathan Tanner. All rights reserved.
//

#import "NSTextField.h"

@implementation CSTextFieldCallback {
    std::function<bool(std::string)> function;
}

- (id) initWithFunction:(std::function<bool(std::string)>)functionTMP {
    if (self = [self init]) {
        function = functionTMP;
        return self;
    } else {
        return nil;
    }
}

- (BOOL)control:(NSControl*)control textShouldEndEditing:(NSText*)fieldEditor {
    return function([[fieldEditor string] stdString]);
}

@end

@implementation NSTextField (CSCallbacks)

- (CSTextFieldCallback*) setCallback:(std::function<bool(std::string)>)callback {
    CSTextFieldCallback* delegate = [[CSTextFieldCallback alloc] initWithFunction: callback];
    [self setDelegate: delegate];
    return delegate;
}

@end
