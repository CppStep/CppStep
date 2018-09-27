//
//  NSString.m
//  VDJartnet
//
//  Created by Jonathan Tanner on 26/09/2018.
//  Copyright © 2018 Jonathan Tanner. All rights reserved.
//

#import "NSString.h"

@implementation NSString (stdString)

- (id) initWithStdString:(std::string)stdString {
    return [self initWithUTF8String:stdString.c_str()];
}

- (std::string) stdString {
    return std::string([self UTF8String]);
}

@end
