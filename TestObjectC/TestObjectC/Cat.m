#import "Cat.h"

@implementation Cat

-(void) move{
    [super move];
    NSLog(@"walk \n");
}

-(NSString*)description{
    return @"I am a cat. miao miao.\n";
}

-(void) setOwner:(Person*) newOwner{
    mOwner = newOwner;
}
-(Person*) owner{
    return mOwner;
}
@end
