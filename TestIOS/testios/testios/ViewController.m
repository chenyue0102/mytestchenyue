//
//  ViewController.m
//  testios
//
//  Created by chenyue on 2020/9/14.
//  Copyright © 2020 chenyue. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    UILabel *label = [[UILabel alloc]init];
    label.text = @"hello world";
    [label sizeToFit];
    label.center = self.view.center;
    [self.view addSubview: label];
    
    UIButton *button = (UIButton*)[self.view viewWithTag:1];
    [button setTitle:@"change" forState:(UIControlState)UIControlStateNormal];
    [button addTarget:self action: @selector(onClickUnity) forControlEvents:UIControlEventTouchDown];
}
     
- (void) onClickUnity{
     UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"Alert Title"
                                                                                 message:@"The message is ..."
                                                                          preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        //do nothing
    }];
    [alertController addAction:okAction];
    [self presentViewController:alertController animated:FALSE completion:nil];
}


@end
