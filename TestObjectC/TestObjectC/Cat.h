#import "Animal.h"

@class Person;
@interface Cat : Animal {
    @private
    Person *mOwner;
}
-(void) move;
-(NSString*)description;
-(void) setOwner:(Person*) newOwner;
-(Person*) owner;
@end