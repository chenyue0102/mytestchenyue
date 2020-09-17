//
//  ViewController.m
//  testios
//
//  Created by chenyue on 2020/9/14.
//  Copyright © 2020 chenyue. All rights reserved.
//

#import "ViewController.h"
#import "UnityHelper.h"

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    unityHelper = [[UnityHelper alloc]init];
    // Do any additional setup after loading the view.
//    messageout = [[UILabel alloc]init];
//    messageout.text = @"hello world";
//    [messageout sizeToFit];
//    messageout.center = self.view.center;
//    [self.view addSubview: messageout];
    
    
    UIButton *button = (UIButton*)[self.view viewWithTag:1];
    [button setTitle:@"change" forState:(UIControlState)UIControlStateNormal];
    [button addTarget:self action: @selector(onClickTest) forControlEvents:UIControlEventTouchDown];
    
    UIButton *btnInitUnity = (UIButton*)[self.view viewWithTag:2];
    [btnInitUnity addTarget: self action:@selector(onClickInitUnity) forControlEvents:UIControlEventTouchDown];
    
    UIButton *btnShowUnity = (UIButton*)[self.view viewWithTag:3];
    [btnShowUnity addTarget:self action:@selector(onClickShowUnity) forControlEvents:UIControlEventTouchDown];
    
    messageout = (UITextView*)[self.view viewWithTag:4];
}
     
- (void) onClickTest{
     UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"Alert Title"
                                                                                 message:@"The message is ..."
                                                                          preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        //do nothing
    }];
    [alertController addAction:okAction];
    [self presentViewController:alertController animated:FALSE completion:nil];
}

-(void) onClickInitUnity{
    extern int g_argc;
    extern char ** g_argv;
    NSDictionary *g_launchOptions;
    bool ret = [unityHelper initUnity:"com.unity3d.framework" argc:g_argc argv:g_argv appLaunchOpts:g_launchOptions];
    NSLog(@"init unity:%d", ret);
    [self appendLog: [NSString stringWithFormat:@"init unity result:%d\n", ret]];
}

-(void) onClickShowUnity{
    bool ret = [unityHelper showUnityWindow];
    [self appendLog:[NSString stringWithFormat:@"show unity result:%d\n", ret]];
}

-(void) appendLog:(NSString*)text{
    [messageout setText: [[messageout text] stringByAppendingString:text]];
}
@end
