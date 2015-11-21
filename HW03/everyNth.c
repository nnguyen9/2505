#include "everyNth.h"
#include <stdio.h>
#include <math.h>

uint64_t everyNth(uint64_t Value, uint8_t N) {

   	uint64_t Accum = 0;
	uint64_t temp = Value;

	uint64_t count = 0;
	while (temp > 0) {
		uint64_t multiplier = 1;
		for (int k = 0; k < count; k++) {
			multiplier *= 10;
		}
		Accum += (temp % 10) * multiplier;
		for (int i = 0; i < N; i++) {
			temp = temp / 10;
		}
		count++;
	}

   	return Accum;
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
