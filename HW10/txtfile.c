#include "txtfile.h"

// Read the contents of a text file, formatting and all, and store it in the
// string_t variable pointed to by result.
//
// Pre:
//      str - Points to a valid string_t variable and is not NULL.
//	in - Points to a file stream opened in read mode, and is not NULL.
//
// Returns:
//      If a required dynamic allocation fails (i.e. with string_insert), 
//	the function will return false, true otherwise.
//
// Other thoughts:
//	Create a temporary char array (perhaps of dimension LINE_CHUNK) 
//	like you've done in previous assignments and use fgets() to read 
//	the file chunk by chunk, inserting the chunks into *result. 
//
bool txtfile_read(FILE *in, string_t * const result)
{
	string_init(result);
	while(!feof(in)) {
		char* buff = malloc(sizeof(char)* (LINE_CHUNK));
		fgets(buff, LINE_CHUNK, in);
		if (!string_insert(result, result->len, buff, strlen(buff))) {
			return false;
		}
	}
	return true;
}

// Read the individual lines (indicated with a "\n") of a text file and 
// store them in the array of string_t variables *result. 
//
// The newline characters are removed by this function.
//
// Pre:
//      result - Points to a string_t * variable that is uninitialized or NULL.
//	in - Points to a file stream opened in read mode, and is not NULL.
//
// Post:
//      *num_lines should be set to the number of lines (string_t) stored in 
//      the array.
//
//      You should not assume num_lines has been initialized prior to calling 
//      txtfile_readlines().
//
//	string_split() is useful for completing this function.
// Returns:
//      If a required dynamic allocation fails (i.e. with string_split()), 
//	the function will return false, true otherwise.
//
//
bool txtfile_readlines(FILE *in, string_t ** const result, size_t * num_lines)
{
	string_t * temp;
	txtfile_read(in, temp);
	
	return string_split(result, temp, "\n", num_lines);
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
