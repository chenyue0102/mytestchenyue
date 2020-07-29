#import <Foundation/Foundation.h>

@interface Animal : NSObject{
	@private
	int mAge;
	@public
	NSString *mName;
}
+(id)createAnimal: (int)age initName: (NSString*)name;
-(id)init:(int)age initName: (NSString*)name;
-(int) age;
-(void) setAge:(int) age;
-(NSString*) name;
-(void) setName:(NSString*) name;
-(void) move;
@end