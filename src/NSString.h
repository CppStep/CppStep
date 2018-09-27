//
//  NSString.h
//  VDJartnet
//
//  Created by Jonathan Tanner on 26/09/2018.
//  Copyright © 2018 Jonathan Tanner. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <string>

NS_ASSUME_NONNULL_BEGIN

@interface NSString (stdString)

- (id) initWithStdString:(std::string)stdString;

- (std::string) stdString;

@end

NS_ASSUME_NONNULL_END
