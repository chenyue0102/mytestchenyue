#import <Foundation/Foundation.h>
#import "Animal.h"

int main (int argc, const char * argv[]) {
   NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	Animal *animal = [[Animal alloc]init:18 : @"kitty"];
   NSLog (@"hello world");
   int age = [animal age];
   NSLog(@"get age:%d name:%@\n", age, [animal name]);
   [pool drain];
   return 0;
}
