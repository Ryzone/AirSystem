#include <stdio.h>
#include <stdlib.h>

signed long *Input;

void main()
{
	unsigned short i,j;
	
	for(;;)
	{
		printf("Type Numbers of Bubble:");
		
		scanf("%hd",&j);
		Input = calloc(j,sizeof(long));
		
		printf("\nType %d Numbers:\n",j);
		
		for(i=0;i<j;i++)
			scanf("%d",&Input[i]);
			
		for(i=0;i<j-1;)
			(*(Input+i) > Input[i+1]) ?	Input[i] ^= Input[i+1],Input[i+1] ^= Input[i],Input[i] ^= Input[i+1],i = 0 : i++;

		for(i=0;i<j;i++)
			printf("%d\t",Input[i]);
	}
}
