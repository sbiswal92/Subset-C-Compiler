#include<stdlib.h>
#include<stdio.h>

void *Malloc(unsigned n)
{
	void *p;
	if(!(p = malloc(n)))
	{
		fprintf(stderr,"Malloc(%d) failed.\n",n);
		fflush(stderr);
		abort();		
	}
	
	return p;
}
