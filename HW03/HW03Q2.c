#include <stdio.h>

int main() {
	// Grabs input file to read
	FILE *input = fopen("ScoreData.txt", "r");

	// Creates or points to output file to write
	FILE *output = fopen("Results.txt", "w");

	// Creates buffer to store line
	char buff[100];
	
	// Loops through, line by line to end of file
	while (fgets(buff, 100, input) != NULL) {
		int id1, id2, score[8];

		// Reset scores
		for (int i = 0; i < 8; i++) {
			score[i] = -1;
		}

		// Gather info from line buffer
		sscanf(buff, "%d-%d\t%d:%d:%d:%d:%d:%d:%d:%d", &id1, &id2, &score[0], &score[1], &score[2], &score[3], &score[4], &score[5], &score[6], &score[7]);
		
		// Output id's
		fprintf(output, "%d%d:\t", id1, id2);
		
		// Calculate average from scores
		int count = 0;
		double average = 0;
		for (int i = 0; i < 8; i++) {
			if (score[i] != -1) {
				average += score[i];
				count++;
			}	
		}
		// Check if any scores were given for that line
		if (average == 0) {
			fprintf(output, "no score data was read\n");
		} else {
			// Output if average exists
			average = average / count;
			fprintf(output, "%4.2f on %d assignments\n", average, count);
		}
	}
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
