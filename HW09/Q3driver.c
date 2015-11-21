#include <stdlib.h>
#include <stdio.h>

#include "Q3bomb.h"

int main(int argc, char** argv) {
   
   if ( argc != 2 ) {
      printf("Must supply a string on the command line.\n");
      exit(1);
   }
   
   Q3bomb(argv[1]);

   return 0;
}
