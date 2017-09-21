#ifndef CHP_H
#define CHP_H


typedef struct _color_map
{
	char *name;
	char *code;
}color_map; // end struct _color_map

cstring * initialize_output_string(cstring *output, char * preamble);
int set_color(const char *color, int foreground);
void help();
int set_prompt(int permanent);
int set_default_prompt(int default_number, int permanent);
#endif // end CHP_H
