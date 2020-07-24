#import <Foundation/Foundation.h>
#import "Animal.h"

void testString(){
   NSString *string = [NSString stringWithFormat : @"testString age:%d name:%@", 1, @"kitty"];
   NSLog(@"%@\n", string);

   NSString *string2 = [NSString stringWithCString: "string"  encoding: NSASCIIStringEncoding];
   NSLog(@"string2:%@\n", string2);
}

int main (int argc, const char * argv[]) {
   NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	Animal *animal = [[Animal alloc]init:18 : @"kitty"];
   
   testString();

   int age = [animal age];
   NSLog(@"animal age:%d name:%@\n", age, [animal name]);

   Animal *animal2 = [Animal createAnimal : 12 name: @"xixi"];
   NSLog(@"animal2 age:%d name:%@ \n", [animal2 age], animal2->mName);
   [pool drain];
   return 0;
}
