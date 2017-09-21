#ifndef CSTRING_H
#define CSTRING_H



typedef struct _cstring
{
	char *str;
	int lenght;
	int size;
}cstring; // end struct _cstring


cstring * create_string(const int initial_size);
void destroy_string(cstring **string);
cstring * append_to_string(cstring *old_string, const char *postscript);

#endif // end CSTRING_H
