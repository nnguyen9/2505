#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

#include "everyNth.h"

void testEveryNth();

int main(int argc, char** argv) {

   testEveryNth();
   
   return 0;
}

void testEveryNth() {

   // You can hardwire values (below and recompile) to test your solution.
   uint64_t Value = 3975177512690566755;
   uint8_t  N     =     1;

   uint64_t Result = everyNth(Value, N);

   printf("%21"PRIu64"%3"PRIu8"%21"PRIu64"\n", Value, N, Result);

}
