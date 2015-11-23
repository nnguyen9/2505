#include "string_type.h"
#include "bytes.c"

//
//
//
//
void string_init(string_t * const str)
{
	// Use the bytes_init function, it will set up almost everything.
	bytes_init(&str->bytes);

	uint8_t null_byte[] = {0};
	// Add a NULL terminator to bytes, now it looks like a C string.
	bytes_insert(&str->bytes, 0, null_byte, 1);

	// We don't count the terminator, so the string is empty.
	str->len = 0;
}


//
//
//
//
void string_free(string_t * const str)
{
	// If there's any dynamic memory holding the string,
	// bytes_free will get rid of it.
	bytes_free(&str->bytes);
}

// Status functions, these are one-liners:

// Is *str empty?
//
// Pre:
//	str - Points to a valid string_t variable and is not NULL.
//
// Returns:
//	Returns true if str->len is 0, false otherwise.
//
bool string_empty(const string_t * const str)
{
	return str->len == 0;
}

// Accessor function, gets the len of the string_t, str->len.
//
// Pre:
//	str - Points to a valid string_t variable and is not NULL.
//
// Returns:
//	Returns str->len.
//
size_t string_len(const string_t * const str)
{
	return str->len;
}


// Accessor function, gets the raw uint8_t pointer via bytes_data().
// We'll treat bytes_data(&str->bytes) like a char *, which is what we'd want 
// for a string type (and is what the function returns.)
//
// Pre:
//	str - Points to a valid string_t variable and is not NULL.
//
// Returns:
//	Returns bytes_data(&str->bytes).
//
char * string_c_str(const string_t * const str)
{
	return bytes_data(&str->bytes);
}


// Gets one character in the string_t variable.
//
// Pre:
//	str - Points to a valid string_t variable and is not NULL.
//
// Post:
//	If index < str->len, then the character at str->bytes.data[index] is 
//	stored into the target of the char*, out.
//
// Returns:
//	If the function could get the character at index (so index < str->len)
//	it will return true, false otherwise.
//
bool string_get(const string_t * const str, size_t index, char * const out)
{
	if (index < str->len) {
		*out = str->bytes.data[index];
		return true;
	} 
	return false;
}


// Sets one character in the string_t variable.
//
// Pre:
//	str - Points to a valid string_t variable and is not NULL.
//
// Post:
//	If index < str->len, then the character at str->bytes.data[index] has 
//	been set to the char, in.
//
// Returns:
//	If the character at index was set (i.e. index < str->len) the 
//	function will return true, false otherwise.
//
bool string_set(string_t * const str, size_t index, char in)
{
	if (index < str->len) {
		bytes_set(&str->bytes, index, in);
		return true;
	}
	return false;
}


// Inserts up to len characters, stored in the memory pointed to by buf, into 
// *str starting at the specified index.
//
// Pre:
//	str - Points to a valid string_t variable and is not NULL.
//	buf - Points to a C string of up to len characters long. It may be 
//	shorter (stop when you find a null terminator and don't include it) 
//	or it may not be null terminated (just insert len characters).
//
// Post:
//	Up to len characters in buf are inserted into *str starting at index.
//	Ensure your internal string data is still null terminated.
//
// Returns:
//	If a required dynamic allocation fails (i.e. with bytes_insert()), or 
//	if index > str->len the function will return false, true otherwise.
//
// Other thoughts:
//	You are going to insert "before" index. So if you insert at index = 0 
//	you are inserting before the first character. Further, if you were to 
//	insert at index = str->len, it's like appending the characters at 
//	the end.
//
bool string_insert(string_t * const str, size_t index, 
			const char * const buf, size_t len)
{
	if (index > str->len) {
		return false;
	}
	str->len = str->len + len;
	return bytes_insert(&str->bytes, index, buf, len);
}


// Erases up to len characters from *str starting at the specified index.
//
// Pre:
//	str - Points to a valid string_t variable and is not NULL.
//
// Post:
//	If index < str->len, then up to len characters have been erased from
//	*str starting at index. When index + len > str->len less than
//	len characters will be erased.
//
//	Ensure your internal string data is still null terminated. Do
//	not erase the null terminator, no matter how characters are erased.
//
// Returns:
//	If index >= str->len, then no erasure occurs and the function
//	returns false, true otherwise.
// 
bool string_erase(string_t * const str, size_t index, size_t len)
{
	if (index >= str->len) {
		return false;
	}
	str->len = str->len - len;
	return bytes_erase(&str->bytes, index, len);
}


// Splits the string_t up into several sub string_t variables using the 
// characters in split as the delimiters. I'd recommend looking into strtok().
//
// Pre:
// 	str - Points to a valid string_t variable and is not NULL.
//	split - Is a C string containing the delimiters used to break up 
//	the string_t. 
//	result - Points to an uninitialized or NULL string_t * variable.
//
//  Post:
//	*result points to a dynamically allocated array of string_t 
//	variables, for example here we split by the characters " \t\n": 
//
// 		"Hello World" --> {"Hello", "World"}
//		"Hello  \tWorld  " --> {"Hello", "World"}
//		"CS2505 Fall\t2015\n" -->{"CS2505", "Fall", "2015"}
//
//	*num_splits should be set to the number of items stored in the 
//	new array *result.
//
//	You should not assume num_splits has been initialized prior to calling 
//	string_split().
//
//	Remember each of the resulting strings above is a string_t, so len 
//	and bytes should be set to appropriate values. For example, if 
// 	your array of string_t variables was called result, and you were 
//	spliting a string_t containing "Hello World" like above, result 
//	would look like: 
//
//	result[0].bytes = {.data="Hello", .usage=6, .dim=16}
//	result[0].len = 5
//
//	result[1].bytes = {.data="World", .usage=6, .dim=16}
//	result[1].len = 5
//      
//	A string_t with only delimiters (whitespace in this example) should 
//	return false, set *result to NULL and num_splits = 0.
//
//	Further, *str should be not be modified by this function!
//
// Returns:
//	If dynamic allocation fails or the case mentioned above 
//	occurs (a string_t with only delimiters) this function will 
//	return false, true otherwise.
//
bool string_split(string_t ** const result, const string_t * const str, 
			const char * const split, size_t * num_splits)
{
	// char orig[str->len];
	// char * origP = strcpy(orig, string_c_str(str));
	// char temp[256];
	// char * temp2 = strcpy(temp, string_c_str(str));
	// //printf("orig String: %s\n", string_c_str(str));
	// char * token = strtok(temp2, split);
	//  //printf("orig String: %s\n", string_c_str(str));

	// if (token == NULL) {
	// 	return false;
	// }

	// size_t count = 0;
	// while (token != NULL) {
	// 	count++;
	// 	token = strtok(NULL, split);
	// }

	// *num_splits = count;
	// printf("Count: %d", count);
	// *result = (string_t*)calloc(count, sizeof(struct string_t));
	// if (*result == NULL) {
	// 	printf("result is null");
	// }
	// temp2 = strcpy(temp, string_c_str(str));
	

	// char * token2 = strtok(temp2, split);
	
	// count = 0;
	// while (token2 != NULL) {
	// 	printf("Token 2: %s\nCount: %d\n", token2, count);
	// 	string_t * tempString;
	// 	tempString = (string_t*)malloc(sizeof(struct string_t));
	
	// 	string_init(tempString);
	// 	if (!string_insert(tempString, 0, token2, strlen(token2))) {
	// 		return false;
	// 	}

	// 	result[count] = tempString;
	// 	printf("CHeck token: %s\n", string_c_str(result[count]));

	// 	token2 = strtok(NULL, split);
	// 	count++;
	// }
	// printf("Out of loop\n");
	// printf("orig String: %s\n", string_c_str(str));
	
	// for (size_t w = 0; w < count; w++)
 //        {
 //                printf("Token %d is:\n\"%s\"\n", w, string_c_str(result[w]));
 //        }


	// string_init(str);
	// string_insert(str, 0, origP, strlen(origP));
	// *num_splits = count;

	char * temp;
	temp = malloc(str->len + 2);
	strcpy(temp, string_c_str(str));

	string_t * tempRes;
	int count = 0;

	char * token = strtok(temp, split);
	if (!token) {
		return false;
	}
	while (!token) {
		tempRes = realloc(res, sizeof(string_t) * (count + 2));
		string_init(&tempRes[count]);
		if (!string_insert(&tempRes[count], 0, token, strlen(token))) {
			return false;
		}
		count++;
		token = strtok(NULL, split);
	}

	*num_splits = count;
	*result = tempRes;

	return true;
}


// Free an array produced by the string_split() function.
//
// Pre:
//	words - Points to an array of string_t variables and is not NULL. The
//	array should have num_words elements.
//
// Post:
//	The dynamic memory for each string_t in the array and the array itself
//	have been deallocated.
//
//
void string_free_split(string_t * words, const size_t num_words)
{
	// Free each string one by one.
	for (size_t s = 0; s < num_words; s++)
	{
		string_free(&words[s]);
	}

	// Then free the array holding them.
	free(words);
}


// The reverse of the split function, this function joins an array of 
// string_t variables together using sep as the "glue".
//
// Pre:
// 	result - Points to a valid string_t variable and is not NULL.
//	words - Points to an array of string_t variables and is not NULL. The
//	array should have num_words elements.
//	sep - Is a C string containing the characters that will go between
//	the string_t variables in the *result.
//
// Example:
// 		{"Hello", "World"} with sep = " " --> "Hello World"
// 		{"Hello", "World"} with sep = "\t" --> "Hello\tWorld"
// 		{"Hello", "World"} with sep = "CS2505" --> "HelloCS2505World"
// Note:
//	Only add sep between two string_t variables, so there shouldn't be
//	an extra sep after "World" in the above examples.
//
// Returns:
//	If a required dynamic allocation fails (i.e. with string_insert()), 
//	the function will return false, true otherwise.
//
bool string_join(string_t * const result,  const string_t * const words, 
			const size_t num_words, const char * const sep)
{
	string_init(result);
	for (int i = 0; i < num_words; i++) {
		if (!string_insert(result, result->len, string_c_str(&words[i]), strlen(string_c_str(&words[i])))) {
			return false;
		}
		if (i < num_words - 1) {
			if (!string_insert(result, result->len, sep, strlen(sep))) {
				return false;
			}
		}
	}
	return true;
}


// Makes a deep copy of *src and stores it in *dest. Similar to *dest = *src.
//
// Pre:
//	src - Points to a valid string_t variable and is not NULL.
//	dest - Points to a valid string_t variable and is not NULL.
//
// Post:
//	If successful then *dest contains a copy of *src. Both *src and *dest
//	should be completely separate entities. Changing one should not 
//	affect the other.
//
// Returns:
//	If copying *src into *dest succeeds the function will return true.
//	If dynamic allocation is required, but fails this function will
//	return false.
//
bool string_copy(string_t * const dest, const string_t * const src)
{
	return bytes_copy(&dest->bytes, &src->bytes);
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
