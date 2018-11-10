//
//  NSFunction.mm
//  VDJartnet
//
//  Created by Jonathan Tanner on 19/10/2018.
//  Copyright © 2018 Jonathan Tanner. All rights reserved.
//

#import "NSPair.h"

@implementation NSPair
- (id) initWithFirst:(id)first second:(id)second {
    if (self = [super init]) {
        [self setFirst:first];
        [self setSecond:second];
        return self;
    } else {
        return nil;
    }
}
@end
