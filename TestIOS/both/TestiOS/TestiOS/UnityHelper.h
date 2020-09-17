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
//#import <Libraries/Plugins/iOS/NativeCallProxy.h>

@class UnityFramework;
@interface UnityHelper : UIResponder<UnityFrameworkListener/*, NativeCallsProtocol*/>{
@private UnityFramework *ufw;
}

-(id)init;
-(bool) unityIsInitialized;
-(bool)initUnity:(const char*)dataBundleId argc:(int)argc argv:(char*[])argv appLaunchOpts:(NSDictionary*)appLaunchOpts;
-(bool)showUnityWindow;
@end
#endif /* UnityHelper_h */
