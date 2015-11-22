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
	char* buff = malloc(sizeof(char)* (LINE_CHUNK));
	fgets(buff, LINE_CHUNK, in);
	string_init(result);
	return string_insert(result, 0, buff, strlen(buff));
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
	printf("Start ReadLine\n");
	*num_lines = 0;
	int offset = 0;
	while (!feof(in)) {    
		char* buff = malloc(sizeof(char)* (LINE_CHUNK));
	    printf("start while\n");
	    // Gets number of words from first line
	    fgets(buff, LINE_CHUNK, in);  
	    
	    string_init(&result[offset]);
	    printf("string initialized\n");
	    if (!string_insert(&result[offset], 0, buff, strlen(buff))) {
	    	return false;
	    }
	    bytes_fprintf(stdout, &result[offset]->bytes);
	    printf("Line\n");
	    offset++;
	    *num_lines = *num_lines + 1;
    }
	printf("readLines done\n");
	
	return true;
}

