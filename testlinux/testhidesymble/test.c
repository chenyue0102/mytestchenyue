#include <stdio.h>
#include <dlfcn.h>
#include "lib1/call1.h"
#include "lib2/call2.h"

typedef void (*CALLFUN)(void);
int main(void){
	const char *dl1 = "./libso1.so";
	const char *dl2 = "./libso2.so";
	void *lib1 = dlopen(dl1, RTLD_NOW);
	void *lib2 = dlopen(dl2, RTLD_NOW);
	if (NULL == lib1 || NULL == dl2){
		printf("dlopen failed\n");
		return -1;
	}
	CALLFUN cal1 = (CALLFUN)dlsym(lib1, "call1");
	CALLFUN cal2 = (CALLFUN)dlsym(lib2, "call2");
	if (NULL == cal1 || NULL == cal2){
		printf("dlsym failed\n");
		return -1;
	}
	cal1();
	cal2();
	//call1();
	//call2();
	return 0;
}