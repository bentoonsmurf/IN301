#include <stdlib.h>
#include <stdio.h>
#include "circonferance.h"
#include "surface.h"
#include "pi.h"

void main(){
	float r =7.0;
	float c,s;
	c=circonf(r);
	printf("circonferance  %f \n",c);
	
	s=surface(r);
	printf("surface %f \n",s);
	
	
	
	
}
