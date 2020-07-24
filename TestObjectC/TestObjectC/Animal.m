#import <Foundation/Foundation.h>
#import "Animal.h"

@implementation Animal
-(id)init:(int)age : (NSString*) name{
	mAge = age;
	mName = name;
	return self;
}

-(int) age{
	NSLog(@"call age method\n");
	return mAge;
}
-(void) setAge:(int) age{
	NSLog(@"call setAge method age:%d\n", age);
	mAge = age;
}

-(NSString*) name{
	return mName;
}
-(void) setName:(NSString*) name{
	mName = name;
}
@end