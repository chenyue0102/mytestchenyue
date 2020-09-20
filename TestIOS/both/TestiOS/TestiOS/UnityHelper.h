//
//  UnityHelper.h
//  testios
//
//  Created by chenyue on 2020/9/15.
//  Copyright © 2020 chenyue. All rights reserved.
//

#ifndef UnityHelper_h
#define UnityHelper_h
#import <UnityFramework/UnityFramework.h>


@class UnityFramework;
@protocol NativeCallsProtocol;
@interface UnityHelper : UIResponder<UnityFrameworkListener>{
@private UnityFramework *ufw;
}

-(id)init;
-(bool) unityIsInitialized;
-(bool)initUnity:(const char*)dataBundleId argc:(int)argc argv:(char*[])argv appLaunchOpts:(NSDictionary*)appLaunchOpts aApi:(id<NativeCallsProtocol>)aApi;
-(bool)showUnityWindow;
-(void)UnitySendMessage:(const char*)jsonText;
@end
#endif /* UnityHelper_h */
