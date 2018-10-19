//
//  NSFunction.mm
//  VDJartnet
//
//  Created by Jonathan Tanner on 19/10/2018.
//  Copyright © 2018 Jonathan Tanner. All rights reserved.
//

#import "NSFunction.h"

@implementation NSFunction {
    std::function<void()> _function;
}
- (id) initWithFunction:(std::function<void()>)function {
    if (self = [super init]) {
        _function = function;
        return self;
    } else {
        return nil;
    }
}
- (void) execute {
    _function();
}
@end
