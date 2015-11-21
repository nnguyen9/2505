#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

#include "BinaryInt.h"

void testBinaryInt();

int main(int argc, char** argv) {

	testBinaryInt();
   
	return 0;
}

void testBinaryInt() {

	uint8_t A[32];
	uint8_t B[32];

	BI_Create(A, 167492527);
	BI_Create(B, -1064267421);

	BI_fprintf(stdout, A, "-2: ", "\n");
	BI_fprintf(stdout, B, "3: ", "\n");

	uint8_t sum[32];
	if (BI_Add(sum, A, B, UNSIGNED)) {
		BI_fprintf(stdout, sum, "Sum: ", "\n");
	} else {
		printf("overflow error\n");
	}

	uint8_t C[32];

	BI_Create(C, 1064267421);
	BI_fprintf(stdout, C, "1064267421: ", "\n");

	uint8_t neg[32];
	if (BI_Neg(neg, C)) {
		BI_fprintf(stdout, neg, "Neg: ", "\n");
	} else {
		printf("overflow error\n");
	}

	uint8_t D[32];
	BI_Create(D, -1554321342);
	BI_fprintf(stdout, D, "-1554321342: ", "\n");

	int64_t decimalVal2 = BI_ToDecimal(D, SIGNED);
	int64_t decimalVal = BI_ToDecimal(D, UNSIGNED);

	printf("Signed Decimal: %" PRId64 "\n", decimalVal2);
	printf("UnSigned Decimal: %" PRId64 "\n", decimalVal);

	uint8_t E[32];
	uint8_t F[32];

	BI_Create(E, 167492527);
	BI_Create(F, 1064267421);
	BI_fprintf(stdout, E, "167492527: ", "\n");
	BI_fprintf(stdout, F, "1064267421: ", "\n");

	uint8_t diff[32];
	if (BI_Sub(diff, E, F, UNSIGNED)) {
		BI_fprintf(stdout, diff, "Subtraction: ", "\n");
	} else {
		printf("overflow error\n");
	}
}
