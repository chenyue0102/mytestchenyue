//
//  main.m
//  TestiOS
//
//  Created by chenyue on 2020/9/16.
//  Copyright © 2020 chenyue. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"

int g_argc = 0;
char **g_argv = nil;
int main(int argc, char * argv[]) {
    g_argc = argc;
    g_argv = argv;
    NSString * appDelegateClassName;
    @autoreleasepool {
        // Setup code that might create autoreleased objects goes here.
        appDelegateClassName = NSStringFromClass([AppDelegate class]);
    }
    return UIApplicationMain(argc, argv, nil, appDelegateClassName);
}
