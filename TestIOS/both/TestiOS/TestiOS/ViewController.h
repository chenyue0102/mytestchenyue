//
//  ViewController.h
//  testios
//
//  Created by chenyue on 2020/9/14.
//  Copyright © 2020 chenyue. All rights reserved.
//

#import <UIKit/UIKit.h>

@class UnityHelper;
@interface ViewController : UIViewController{
@private UnityHelper *unityHelper;
@private UITextView *messageout;
}
-(void) onClickTest;
-(void) onClickInitUnity;
-(void) onClickShowUnity;
-(void)appendLog:(NSString*)text;
@end

