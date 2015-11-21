#include "swap_if.h"

/* Pre:
 *  a[]: contains aUsage values
 *  b[]: contains bUsage values
 *
 * Post:
 *  For each element i: 
 *      - If both a[i] and b[i] are even, then swap the 
 *        values between the arrays, so a[i] contains the value of b[i] and
 *        vice versa.
 *
 *      - If both a[i] and b[i] are odd, swap the next values in the arrays, 
 *        so a[i] = b[i + 1] and b[i] = a[i + 1]. If there isn't a 
 *        next value in both arrays don't change either array.
 *
 *      - Otherwise replace a[i] and b[i] with the max(a[i], b[i])
 *
 * If the lengths differ, i.e. aUsage != bUsage, use the minimum of the two
 * leaving the remainder of the longer array untouched.
 * 
 * Returns:
 *  The number of modifications made.
 */
uint32_t swap_if(uint32_t a[], uint32_t aUsage, uint32_t b[], uint32_t bUsage)
{

	// Find the smallest of the two array sizes
	uint32_t lengthTrav;
	if (aUsage > bUsage) {
		lengthTrav = bUsage;
	} else {
		lengthTrav = aUsage;
	}

	// Initialize the counter number of swaps
	uint32_t count = 0;

	// Traverse array
	for (int i = 0; i < lengthTrav; i++) {
		
		if (a[i] % 2 == 0 && b[i] % 2 == 0) {
			// Both even then swap
			uint32_t temp = a[i];
			a[i] = b[i];
			b[i] = temp;
			count++;
		} else if (a[i] % 2 != 0 && b[i] % 2 != 0) {
			// Both odd, replace with next
			if (lengthTrav - i > 1) {
				a[i] = b[i + 1];
				b[i] = a[i + 1];
				count++;
			}
		} else {
			// One odd, one even, replace with max
			if (a[i] > b[i]) {
				b[i] = a[i];
			} else {
				a[i] = b[i];
			}
			count++;
		}
	}

	// Return the number of modifications
	return count;
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

