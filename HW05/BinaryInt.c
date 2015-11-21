#include "BinaryInt.h"
#include <inttypes.h>

// Internal representation stores bits so that coefficient of 2^i is at index i.

/**
 *   Initializes BinInt[] so that the elements correspond to the binary
 *   representation of the low 32 bits of integer Src.
 * 
 *   Pre:   BinInt[] is of dimension 32
 *   Post:  For i = 0 to 31, BinInt[i] == 2^i bit of Src
 */
void BI_Create(uint8_t BinInt[], int64_t Src) {
   
   int32_t Mask = 0x01;
   for (int pos = 0; pos < NUM_BITS; pos++) {
      BinInt[pos] = ( Src & Mask) ? 1 : 0;
      Mask = Mask << 1;
   }
}

/**
 *   Computes sum of the signed/unsigned integer values.
 * 
 *   Pre:   Sum[], Left[] and Right[] are of dimension 32
 *          Left[] and Right[] store 2's complement or unsigned representations
 *          DR matches the representation of both Left[] and Right[]
 *   Post:  Sum[] == Left[] + Right[], if possible
 *   Ret:   false if overflow occurs when computing sum of Left[] and Right[];
 *          true otherwise
 */
bool BI_Add(uint8_t Sum[], const uint8_t Left[], 
		const uint8_t Right[], enum DataRep DR) 
{
	// Tracks if a 1 is carried over from addition
	bool carryOver = false;
	bool carryIn;

	// Loops through the 32 indexes
	for (int i = 0; i < 32; i++) {
		// Adds the 2 indexes of the arrays
		uint8_t addSum = Left[i] + Right[i];

		// If there is a carryOver, adds 1
		if (carryOver) {
			addSum++;
			carryOver = false;
		}

		// A 3 will leave a 1 and carry over
		if (addSum == 3) {
			Sum[i] = 1;
			carryOver = true;
		} else if (addSum == 2) {
		// A 2 will leave a 0 and carry over
			Sum[i] = 0;
			carryOver = true;
		} else if (addSum == 1) {
		// A 1 will leave a 1 and not carry over
			Sum[i] = 1;
			carryOver = false;
		} else {
		// A 0 will leave a 0 and not carry over
			Sum[i] = 0;
			carryOver = false;
		}

		// Checks overflow
		if (i == 30) {
			carryIn = carryOver;
		}
	}

	// If carrying in to the 32nd index is not equal
	// to the carrying out then overflow has occured
	if (carryOver != carryIn) {
		return false;
	}

   	return true;
}

/**
 *   Computes difference of the signed/unsigned integer values.
 * 
 *   Pre:   Diff[], Left[] and Right[] are of dimension 32
 *          Left[] and Right[] store 2's complement or unsigned representations
 *          DR matches the representation of both Left[] and Right[]
 *   Post:  Diff[] == Left[] - Right[], if possible
 *   Ret:   false if overflow occurs when computing difference of Left[]
 *          and Right[]; true otherwise 
 */
bool BI_Sub(uint8_t Diff[], const uint8_t Left[], 
		const uint8_t Right[], enum DataRep DR) 
{
	uint8_t tempRight[32];
	// Takes the negative of the right number
	if (BI_Neg(tempRight, Right)) {
	// Adds to the left number
		if (BI_Add(Diff, Left, tempRight, DR)) {
			if (DR == UNSIGNED) {
				// Overflow if the last spot is a 1 but others aren't
				if (Diff[31] == 1 && Left[31] != 1 && Right[31] != 1) {
					return false;
				} else {
					return true;
				}
			} else {
				return true;
			}
		} else {
			return false;
		}
	} else {
		return false;
	}
}

/**
 *   Computes negation of 2's complement representation of integer value.
 * 
 *   Pre:   Neg[] and Right[] are of dimension 32
 *          Right[] stores a 2's complement representation
 *   Post:  Neg[] = -Right[]
 *   Ret:   false if negation cannot be correctly represented; 
 *          true otherwise
 */
bool BI_Neg(uint8_t Neg[], const uint8_t Right[]) {
	// Take one's complement by switching all 1's to
	// 0's and all 0's to 1's
	for (int i = 0; i < 32; i++) {
		if (Right[i] == 0) {
			Neg[i] = 1;
		} else {
			Neg[i] = 0;
		}
	}

	// Gets the Twos complement of 1
	uint8_t BI_one[32];
	BI_Create(BI_one, 1);

	// Adds one to finish negative twos complement
   	return BI_Add(Neg, BI_one, Neg, UNSIGNED);
}

/**
 *   Converts a BinInt[] to its decimal representation.
 * 
 *   Pre:   Num[] is of dimension 32
 *          Num[] stores a 2's complement or unsigned representation
 *          DR matches the representation of Num[]
 *   Ret:   The decimal value.
 */
int64_t BI_ToDecimal(uint8_t Num[], enum DataRep DR)
{
	// Initialize values
	int64_t decimalValue = 0;
	int endIndex;
	bool neg = false;

	// Stores num into temp and copies values over
	uint8_t tempNum[32];

	for (int i = 0; i < 32; i++) {
		tempNum[i] = Num[i];
	}

	// If it's a signed integer check the sign
	if (DR == SIGNED) {
		// Signed integer only checks up to the 31st spot
		endIndex = 31;
		// If it's negative then negate to get positive
		if (Num[31] == 1) {
			neg = true;
			BI_Neg(tempNum, tempNum);
		}
	} else {
		// Unsigned integer checks all locations
		endIndex = 32;
	}

	// Loop through array
	for (int i = 0; i < endIndex; i++) {
		// If the index is 1 then add 2^i to the value
		// 1 << i == 2^i
		if (tempNum[i] == 1) {
			decimalValue = decimalValue + (1L << i);
		}
	}

	// Checks if the integer is supposed to be negative
	// from above
	if (neg) {
		decimalValue = decimalValue * -1;
	}

	// return decimalValue;
	return decimalValue;
}


/**
 *   Prints the binary representation, with formatting.
 * 
 *   Pre:   fp is open on an output stream
 *          BinInt[] is of dimension 32 and stores a 2's complement
 *          or unsigned representation
 *          prefix and suffix are each NULL or point to a C-string
 *   Post:  the bits represented in BinInt[] have been written, preceded by
 *          prefix (if not NULL) and followed by suffix (if not NULL)
 */
void BI_fprintf(FILE* fp, const uint8_t BinInt[], char* prefix, char* suffix) {
   
   if ( prefix != NULL)
      fprintf(fp, prefix);
      
   for (int pos = NUM_BITS - 1; pos >= 0; pos--) {
       if ( pos < NUM_BITS - 1 && pos % 4 == 3 )
          fprintf(fp, " ");
     
      fprintf(fp, "%"PRIu8, BinInt[pos]);
   }
   
   if ( suffix != NULL)
      fprintf(fp, suffix);
}

//On my honor:
//
//-I have not discussed the C language code in my program with
// anyone other than my instructor or the teaching assistants 
// assigned to this course.
//
//-I have not used C language code obtained from another student, 
// or any other unauthorized source, either modified or unmodified.  
//
//-If any C language code or documentation used in my program 
// was obtained from an allowed source, such as a text book or course
// notes, that has been clearly noted with a proper citation in
// the comments of my program.
//
// Nam Nguyen
