#import <Foundation/Foundation.h>
#import "Animal.h"

@implementation Animal

+(id)createAnimal:(int)age initName:(NSString*)name{
	NSLog(@"createAnimal begin");
	Animal *animal = [[Animal alloc]init : age initName: name];
	return animal;
}

-(id)init:(int)age initName: (NSString*)name {
	if ((self = [super init])){
		mAge = age;
		mName = name;
	}
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

-(void) move{
	NSLog(@"move\n");
}

@end