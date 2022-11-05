#include<stdio.h>

#include<stdlib.h>



unsigned power (unsigned x, unsigned y);

int main(void){

  if (power(0,0) != 1) return EXIT_FAILURE;

  if (power(5,0) != 1) return EXIT_FAILURE;

  if (power(0,5) != 0) return EXIT_FAILURE;

  if (power(5,2) != 25) return EXIT_FAILURE;

  if (power(3*2, 2) != 36) return EXIT_FAILURE;
  
  if (power(5,1) != 5) return EXIT_FAILURE;

  if (power(2,10) != 1024) return EXIT_FAILURE;

  if (power(10,2) != 100) return EXIT_FAILURE;

  if (power(10,5) !=100000) return EXIT_FAILURE;

  if (power(1,0) !=1) return EXIT_FAILURE;
  
  if (power(0,1) !=0) return EXIT_FAILURE;





  return EXIT_SUCCESS;

}
