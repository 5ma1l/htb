#include <stdlib.h>
#include <stdio.h>

typedef unsigned char byte;

int main(){

	FILE *f=fopen("flag.enc","rb");

	fseek(f,0,SEEK_END);
	uint len=ftell(f);
	fseek(f,0,SEEK_SET);
	uint *seed=(uint *)malloc(4);
	
	fread(seed,4,1,f);

	printf("the seed is : %d\n",*seed);

	byte *content=(byte *)malloc(len-4);
	fread(content,len-4,1,f);

	fclose(f);
	srand(*seed);
	uint rand1,rand2;
	
	for (int i=0;i<len-4;i++){
		rand1=rand()&255;
		rand2=rand()&7;

		content[i]=content[i]>>rand2 | content[i]<<(8-rand2);

		printf("the content value after rand2 %d : %c\n",rand2,content[i]);

		content[i]=content[i]^rand1;
		
		printf("the content value after rand1 %d : %c\n",rand1,content[i]);

	}
	
	
	printf("The flag is : %s",content);
	free(content);
	free(seed);
	return 0;

}
