#include <stdio.h>
#include <unistd.h>

int main(char *argc[], int argv)
{
	const char *file_name = "/dev/test_timer";
	FILE *f = fopen(file_name, "rb");
	if (NULL == f){
		printf("open failed %s\n", file_name);
		return 0;
	}
	unsigned int t = -1, old_t = -1;
	while(1){
		
		if (fread(&t, 1, sizeof(unsigned int), f) == sizeof(unsigned int)){
			if (t != old_t){
				printf("t=%d\n", t);
				old_t = t;
			}
			else{
				usleep(200);
			}
		}
		else{
			printf("read size failed\n");
			break;
		}
	}
	fclose(f);
	printf("hello world\n");
	return 0;
}