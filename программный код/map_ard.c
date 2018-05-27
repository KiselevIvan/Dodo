#include <math.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc,char *argv[])
{
 if (argc>=1)
   { 
     int x = atoi(argv[1]);
     int in_min = atoi(argv[2]);
     int in_max = atoi(argv[3]);
     int out_min = atoi(argv[4]);
     int out_max = atoi(argv[5]);
     
printf("%i",(int)round((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min));
	  return (0);
   }  
else
  return -1;
}
