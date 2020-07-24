#import <Foundation/Foundation.h>

@interface Animal : NSObject{
	@private
	int mAge;
	NSString *mName;
}
-(id)init:(int)age : (NSString*)name;
-(int) age;
-(void) setAge:(int) age;
-(NSString*) name;
-(void) setName:(NSString*) name;
@end