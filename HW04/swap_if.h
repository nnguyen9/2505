#ifndef SWAPIF_H
#define SWAPIF_H
#include <stdint.h>

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
uint32_t swap_if(uint32_t a[], uint32_t aUsage, uint32_t b[], uint32_t bUsage);


#endif
