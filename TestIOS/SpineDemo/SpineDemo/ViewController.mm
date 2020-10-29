//
//  ViewController.m
//  SpineDemo
//
//  Created by chenyue on 2020/10/23.
//  Copyright © 2020 chenyue. All rights reserved.
//

#import "ViewController.h"
#include "BaseTime.h"
#include "rendercmdscache.h"
#include "spineitem.h"

@interface ViewController (){
    RenderCmdsCache *mRenderCmdsCache;
    SpineItem *mSpineItem;
    BaseTime *mBaseTime;
    int64_t mLastTime;
}
@property (strong, nonatomic) EAGLContext *context;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
#if 0
    NSString *path = [[NSBundle mainBundle]pathForResource:@"Settings" ofType:@"bundle"];
    UIImage *image = [UIImage imageWithContentsOfFile:[path stringByAppendingPathComponent:@"alien.png"]];
    NSString *jsonPath = [path stringByAppendingPathComponent:@"alien.atlas"];
    const char * jsonChar = [jsonPath UTF8String];
    FILE *f = fopen(jsonChar, "rb");
    fclose(f);
    UIImage *image = [UIImage imageNamed:@"alien.png"];
    int width = image.size.width;
    int height = image.size.height;
    int channel = 4;
    int bytesPerRow = width * channel;
    unsigned char *pixelData = (unsigned char*)malloc(height * bytesPerRow);
    CGContextRef contextRef = CGBitmapContextCreate(pixelData, width, height, 8, bytesPerRow, nil, kCGImageAlphaLast);
    CGContextDrawImage(contextRef, CGRectMake(0, 0, width, height), image.CGImage);
    CGContextRelease(contextRef);
    free(pixelData);
    UIImageView *imageView = [[UIImageView alloc]initWithImage:image];
    imageView.frame = CGRectMake(50, 50, image.size.width, image.size.height);
    [self.view addSubview:imageView];
#endif
    [self setupGL];
    
    //计算动画帧间隔时间类
    mBaseTime = new BaseTime();
    
    NSString *path = [[NSBundle mainBundle]pathForResource:@"Settings" ofType:@"bundle"];
    const char *atlasPath = [[path stringByAppendingPathComponent:@"alien.atlas"] UTF8String];
    const char *jsonPath = [[path stringByAppendingPathComponent:@"alien-ess.json"] UTF8String];
    const char* vTexture = [[path stringByAppendingPathComponent:@"shader/texture.vert"] UTF8String];
    const char* fTexture = [[path stringByAppendingPathComponent:@"shader/texture.frag"] UTF8String];
    const char* vColor = [[path stringByAppendingPathComponent:@"shader/color.vert"] UTF8String];
    const char* fColor = [[path stringByAppendingPathComponent:@"shader/color.frag"] UTF8String];

    spine::Bone::setYDown(false);
    
    mRenderCmdsCache = new RenderCmdsCache();
    //初始化shader
    mRenderCmdsCache->initShaderProgram(vTexture, fTexture, vColor, fColor);
    //设置游戏场景的设计分辨率
    mRenderCmdsCache->setViewSize(MySize(1024.f, 768.f));
    
    mSpineItem = new SpineItem();
    mSpineItem->setAtlasFile(atlasPath);
    mSpineItem->setSkeletonFile(jsonPath);
    mSpineItem->create();
    //mSpineItem->setDebugMesh(true);
    //mSpineItem->setDebugBones(true);
    //mSpineItem->setDebugSlots(true);
    spine::Skeleton *skeleton = mSpineItem->getSkeleton();
    assert(nullptr != skeleton);
    //设置动画位置,0,0 位于中间
    skeleton->setPosition(0.f, 0.f);
    skeleton->setScaleX(1.0f * 2.0f);
    skeleton->setScaleY(1.0f * 2.0f);
    skeleton->updateWorldTransform();
    //设置当前播放动画
    mSpineItem->setAnimation(0, "death", true);
    
    mLastTime = mBaseTime->getCurrentTimeMs();
    
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(onOrientationChanged:) name:UIApplicationDidChangeStatusBarOrientationNotification object:nil];
}

-(void)onOrientationChanged:(NSNotification*)notification{
    int width = self.view.frame.size.width;
    int height = self.view.frame.size.height;
    //mRenderCmdsCache->setViewSize(MySize(width, height));
}

-(void)setupGL{
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    if (nil == self.context){
        NSAssert(false, @"setupGL nil == self.context");
        return;
    }
    
    GLKView *view = (GLKView*)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    [EAGLContext setCurrentContext:self.context];
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

-(void)dealloc{
    [self tearDownGL];
}

-(void)tearDownGL{
    if ([EAGLContext currentContext] == self.context){
        [EAGLContext setCurrentContext:nil];
    }
}

-(void)update{
    int64_t curTime = mBaseTime->getCurrentTimeMs();
    float delta = (curTime - mLastTime) / 1000.f;
    mSpineItem->updateSkeletonAnimation(delta);
    mLastTime = curTime;
}

-(void)glkView:(GLKView *)view drawInRect:(CGRect)rect{
    mSpineItem->batchRenderCmd(mRenderCmdsCache);
    mSpineItem->renderToCache(mRenderCmdsCache);
    mRenderCmdsCache->render();
}
@end
