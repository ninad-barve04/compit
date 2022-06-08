
#include<stdio.h>
#include <string.h>

int main(void)
{

	FILE *fp = fopen("sample1.wav","wb");
	char buffer[1024];
	sprintf(buffer, "milindbarveninadbarve");
	int sz = strlen( buffer) ;
	fwrite(buffer, sz, 1, fp);
	fclose(fp);
}
