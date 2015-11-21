#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

#include "swap_if.h"

void testSwapIf();

int main(int argc, char** argv) {

	testSwapIf();
   
	return 0;
}

void testSwapIf() {

	uint32_t A[6] = {1, 2, 3, 4, 5, 6};
	uint32_t B[5] = {1, 4, 2, 4, 5};

	uint32_t result = swap_if(A, 6, B, 5);
	printf("result: %"PRIu32"\n", result);

}
