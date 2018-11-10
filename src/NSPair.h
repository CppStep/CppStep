//
//  NSFunction.h
//  VDJartnet
//
//  Created by Jonathan Tanner on 19/10/2018.
//  Copyright © 2018 Jonathan Tanner. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSPair<T1, T2> : NSObject
- (id) initWithFirst:(T1)first second:(T2)second;
@property T1 first;
@property T2 second;
@end
