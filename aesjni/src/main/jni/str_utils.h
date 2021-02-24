/**
 * @author Bruce.
 * C++ operating char string is easier than C,so I operate some string and char in there.
 */

#include <stdio.h>

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif
//----------begin---------

typedef void *mylibrary_mytype_t;
EXTERNC int compare_str(unsigned char *unsigned_str, char *str);

EXTERNC void print_chars_in_hex(unsigned char *data, size_t len);
EXTERNC void print_str(unsigned char *data, size_t len);
//----------end---------
#undef EXTERNC