//
//  NSFunction.h
//  VDJartnet
//
//  Created by Jonathan Tanner on 19/10/2018.
//  Copyright © 2018 Jonathan Tanner. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <functional>

@interface NSFunction : NSObject
- (id) initWithFunction:(std::function<void()>)function;
- (void) execute;
@end
