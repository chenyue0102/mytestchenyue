//
//  UnityHelper.m
//  testios
//
//  Created by chenyue on 2020/9/15.
//  Copyright © 2020 chenyue. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UnityHelper.h"

UnityFramework* UnityFrameworkLoad(){
    NSString* bundlePath = nil;
    bundlePath = [[NSBundle mainBundle] bundlePath];
    bundlePath = [bundlePath stringByAppendingString: @"/Frameworks/UnityFramework.framework"];
    
    NSBundle* bundle = [NSBundle bundleWithPath: bundlePath];
    if ([bundle isLoaded] == false) [bundle load];
    
    UnityFramework* ufw = [bundle.principalClass getInstance];
    if (![ufw appController])
    {
        // unity is not initialized
        [ufw setExecuteHeader: &_mh_execute_header];
    }
    return ufw;
}

@implementation UnityHelper

- (void)unityDidUnload:(NSNotification*)notification{
    
}

- (void)unityDidQuit:(NSNotification*)notification{
    
}

- (void) showHostMainWindow:(NSString*)color{
    
}

-(id)init{
    if (self = [super init]){
        ufw = nil;
    }
    return self;
}

-(bool)unityIsInitialized{
    return nil != ufw && nil != [ufw appController];
}

-(bool)initUnity:(const char*)dataBundleId argc:(int)argc argv:(char*[])argv appLaunchOpts:(NSDictionary*)appLaunchOpts{
    bool ret = false;
    
    do {
        if (nil == dataBundleId){
            NSAssert(false, @"nil == dataBundleId failed");
        }
        if (nil != ufw){
            ret = true;
            break;
        }
        if (nil == (ufw = UnityFrameworkLoad())){
            NSAssert(false, @"UnityFrameworkLoad failed");
            break;
        }
        [ufw setDataBundleId: dataBundleId];
        [ufw registerFrameworkListener: self];
        //[NSClassFromString(@"FrameworkLibAPI") registerAPIforNativeCalls:self];
        
        [ufw runEmbeddedWithArgc:argc argv:argv appLaunchOpts:appLaunchOpts];
        [ufw appController].quitHandler = ^{
            NSLog(@"AppController.quitHandler called");
        };
        auto view = [[ufw appController] rootView];
        ret = true;
    } while (false);
    
    return ret;
}

-(bool)showUnityWindow{
    if ([self unityIsInitialized]){
        [ufw showUnityWindow];
        return true;
    }else{
        NSAssert(false, @"unity not init failed");
        return false;
    }
}
@end
