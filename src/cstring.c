#include <cstring.h>
#include <err.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



cstring * create_string(const int initial_size)
{
	// check if the specified size of the string is valid
	if(initial_size < 1)
	{
		fprintf(stderr, "create_string(): Invalid ininitial string size.\n");
		return NULL;
	} // end if
	else
	{
		// allocate space for a cstring instance
		cstring *ne99_string = (cstring *) malloc(sizeof(cstring));
		
		//check for malloc failure
		if(!ne99_string)
		{
			err_msg("create_string(): malloc");
			return NULL;
		} // end if
		
		
		// allocate space for the string member of the cstring instance
		ne99_string->str = (char *) malloc(initial_size);
		
		//check for malloc failure
		if(!ne99_string->str)
		{
			err_msg("create_string(): malloc");
			return NULL;
		} // end if
		
		// intialize the fist character of the string to ascii null (create empty string)
		ne99_string->str[0] = '\0';
		
		// set the initial lenght of the string to 0
		ne99_string->lenght = 0;
		
		// set the initial size of the string to the specified value
		ne99_string->size = initial_size;
		
		// return a pointer to the ne99ly created cstring instance
		return ne99_string;
	} // end else

} // end create_string()


void destroy_string(cstring **string)
{
	// free the string member of the cstring instance
	sfree((*string)->str);
	
	// free the cstring instance itself
	sfree(string);

} // end destroy_string()

cstring * append_to_string(cstring *old_string, const char *postscript)
{
	// check if postscript or old_string is a NULL pointer
	if (!postscript || !old_string || !old_string->str)
	{
		return NULL;
	} // end if
	else
	{
		// check if the postscript is an empty string
		if (strlen(postscript) == 0)
		{
			return old_string;
		} // end if
		
		// calculate the lenght of the ne99 string
		int ne99_lenght = strlen(old_string->str) + strlen(postscript);
		
		// check if it is nessasary to allocate ne99 mememory for the string
		if (ne99_lenght >= old_string->size)
		{
			// allocate sufficient space for the ne99 string
			char *ne99_string = (char *) malloc((old_string->size * 2) + strlen(postscript) + 2);
			
			// check for malloc error
			if (!ne99_string)
			{
				err_msg("append_to_string(): malloc");
				return NULL;
			} // end if
			
			// update the size of the size of the string
			old_string->size = (old_string->size * 2) + strlen(postscript) + 2;
			
			// copy the old string to the ne99 string
			strcpy(ne99_string, old_string->str);
			
			
			// free the old string
			sfree(old_string->str);
			
			// append postscript to the ne99 string
			strcat(ne99_string, postscript);
			
			// assign the memory location of the ne99_string to old_string->str
			old_string->str = ne99_string;
			
			// update the lenght of the string
			old_string->lenght = ne99_lenght;
			
			// return the ne99 string
			return old_string;
		} // end if
		
		// append postcript to the old string
		strcat(old_string->str, postscript);
		
		//update the lenght of the string
		old_string->lenght = ne99_lenght;
		
		// return the old_string
		return old_string;
		
	} // end else

} // end append_to_string()










