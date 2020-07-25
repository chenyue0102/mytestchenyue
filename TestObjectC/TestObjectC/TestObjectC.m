#import <Foundation/Foundation.h>
#import "Animal.h"
#import "Cat.h"
#import "Person.h"

void testString(){
   NSString *string = [NSString stringWithFormat : @"testString age:%d name:%@", 1, @"kitty"];
   NSLog(@"%@\n", string);

   NSString *string2 = [NSString stringWithCString: "string"  encoding: NSASCIIStringEncoding];
   NSLog(@"string2:%@\n", string2);

   if ([string isEqualToString:string2] ){
      NSLog(@"string string2 equal\n");
   }else{
      NSLog(@"string string2 not equal\n");
   }
}

int main (int argc, const char * argv[]) {
   NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	Animal *animal = [[Animal alloc]init:18 initName: @"kitty"];
   
   testString();

   int age = [animal age];
   NSLog(@"animal age:%d name:%@\n", age, [animal name]);

   Animal *animal2 = [Animal createAnimal : 12 initName: @"xixi"];
   NSLog(@"animal2 age:%d name:%@ \n", [animal2 age], animal2->mName);

   Cat *cat = [[Cat alloc] init];
   [cat move];

   NSLog(@"animal: %@\n", cat);

   Person *owner = [cat owner];
   if (NULL == owner){
      NSLog(@"owner null\n");
      Person *newOwner = [[Person alloc]init];
      [cat setOwner: newOwner];
      NSLog(@"owner %@\n", [cat owner]);
   }else{
      NSLog(@"owner %@\n", [owner description]);
   }
   [pool drain];
   return 0;
}
