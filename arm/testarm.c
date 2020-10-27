#include <stdio.h>

int testadd(int a, int b){
	printf("arm %d %d\n", a, b);
	return 5;
}
extern int myfun(int a, int b);
int main(){
	//arm栈向下生长
	int a = 123456;
	int b = 456789;
	asm(
	"ldr r3,[fp,#-12]\n"
	"mov r4,#1 \n"
	"mov r5, #0 \n"
	"add r3, r5, r4, lsl #4 \n"
	
	"ldr r0,[fp, #-8] \n"
	"ldr r1, [fp, #-12] \n"
	"bl testadd \n"
	//参数的结果存储到r0中
	"adds r1, r0, #1 \n"	//将r0+1放到r1中,并修改cond
	"movne r0, #-22 \n"		//如果cond,r1 ne 0,则执行mov命令
	"str r0,[fp, #-12] \n"
	
	"ldr r4, =5555555 \n"
	"movs r1, #2 \n"
	"movmi r4, #2 \n"   //如果r1是负值,则执行此语句
	"str r4, [fp, #-8] \n"
	);
	printf("%d %d\n", a, b);
	
	printf("call myfun %d\n", myfun(2, 3));
	return 0;
}