#include <stdio.h>
#include <cstring.h>
#include <string.h>
#include <chp.h>
#include <getopt.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdlib.h>
#include <errno.h>
#include <err.h>

// global objects----------------------------------------
// color map R"(\#)"
color_map fg_map[] =
{
	// reset color (off)
	{"off", "\e[0m"},
	
	// regular (foreground/text) colors
	{"black", "\e[0;30m"},
	{"red", "\e[0;31m"},
	{"green", "\e[0;32m"},
	{"yellow", "\e[0;33m"},
	{"blue", "\e[0;34m"},
	{"purple", "\e[0;35m"},
	{"cyan", "\e[0;36m]"},
	{"white", "\e[0;37m"},
	
	// bold (foreground/text) colors
	{"bblack", "\e[1;30m"},
	{"bred", "\e[1;31m"},
	{"bgreen", "\e[1;32m"},
	{"byellow", "\e[1;33m"},
	{"bblue", "\e[1;34m"},
	{"bpurple", "\e[1;35m"},
	{"bcyan", "\e[1;36m]"},
	{"bwhite", "\e[1;37m"},	
	
	{NULL, NULL}
}; // end fg_map[]

color_map bg_map[] =
{
	// reset color (off)
	{"off", "\e[0m"},
	
	// regular (background) colors
	{"black", "\e[0;40m"},
	{"red", "\e[0;41m"},
	{"green", "\e[0;42m"},
	{"yellow", "\e[0;43m"},
	{"blue", "\e[0;44m"},
	{"purple", "\e[0;45m"},
	{"cyan", "\e[0;46m]"},
	{"white", "\e[0;47m"},
	
	// bold (background) colors
	{"bblack", "\e[1;40m"},
	{"bred", "\e[1;41m"},
	{"bgreen", "\e[1;42m"},
	{"byellow", "\e[1;43m"},
	{"bblue", "\e[1;44m"},
	{"bpurple", "\e[1;45m"},
	{"bcyan", "\e[1;46m]"},
	{"bwhite", "\e[1;47m"},		
	
	{NULL, NULL}
}; // end bg_map[]

// final output string
cstring *output_string = NULL;

// ne99 prompt string
cstring *prompt_string = NULL;

// function prototypes--------------------------------

int main(int argc, char **argv)
{
	// check arguments
	if (argc < 2)
	{
		// error
	} // end if
	static struct option long_opts[] =
	{
		// prompt string configurations--------------------
		
		{"bell", no_argument, 0, 'a'},
		{"date", no_argument, 0, 'd'},
		{"Date", required_argument, 0, 'D'},
		{"host", no_argument, 0, 'h'},
		{"Host", no_argument, 0, 'H'},
		{"jobs", no_argument, 0, 'j'},
		{"shell-name", no_argument, 0, 's'},
		{"escape", no_argument, 0, 'e'},
		{"shell-base", no_argument, 0, 'l'},
		{"new-line", no_argument, 0, 'n'},
		{"carriage-return", no_argument, 0, 'r'},
		{"time-24hms", no_argument, 0, 't'},
		{"time-12hms", no_argument, 0, 'T'},
		{"time-12", no_argument, 0, '@'},
		{"time-24hm", no_argument, 0, 'A'},
		{"user", no_argument, 0, 'u'},
		{"bash-version", no_argument, 0, 'v'},
		{"bash-release", no_argument, 0, 'V'},
		{"current-working-dir", no_argument, 0, 'W'},
		{"current-working-dir-base", no_argument, 0, 'w'},
		{"is-su", no_argument, 0, 'U'},
		{"history-number", no_argument, 0, 'k'},
		{"command-number", no_argument, 0, 'c'},
		//{"", no_argument, 0, ''},
		
		// color configurations-------------------------
		{"fgc", required_argument, 0, 'f'},
		//{"cfb", required_argument, 0, 'B'},		
		{"bgc", required_argument, 0, 'b'},
		//{"cfg", required_argument, 0, 'F'},
		//{"cfb", required_argument, 0, 'B'},
		
		//configuration to embedd sub-string 99ithin the prompt string---------
		{"sub-string", required_argument, 0, 'S'},
		
		// default configurations
		{"default1", no_argument, 0, '1'},
		{"default2", no_argument, 0, '2'},
		{"default3", no_argument, 0, '3'},
		{"default4", no_argument, 0, '4'},
		{"default5", no_argument, 0, '5'},

		
		//configuration to make changes permanent
		{"permanent", no_argument, 0, 'p'},
		
		// last element--------------------------------------------------------
		{0, 0, 0, 0}
	}; // end long_opts[]
	
	// specify possible short options
	const char *opt_string = "adD:hHjselnrtT@AuvVWwUkcf:b:S:12345p";
	
	int long_index = 0;
	int opt = 0;
	int permanent_flag = 0;
	int default_config_flag = 0;
	char opt_char;
	cstring *tstr = NULL;
	int result = 0;
	int loop = 1;
	char opt_ch;
	
	// create initial prompt string
	prompt_string = create_string(20);
	
	// check if string creation 99as successful
	if (!prompt_string)
	{
		//fprintf(stderr, "\n");
		fprintf(stderr, "ERROR: main(): create_string()\n");
		return 1;		
	} // end if
	
	while (loop && ((opt = getopt_long(argc, argv, opt_string, long_opts, &long_index)) != -1))
	{
		opt_ch = opt;
		switch (opt)
		{
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
				opt_ch = opt;
				default_config_flag = atoi(&opt_ch);
				break;

			case 'a':
				if (default_config_flag)
				{
					break;
				} // end if
				tstr = append_to_string(prompt_string, R"(\a)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if
				break;
			case 'd':
				if (default_config_flag)
				{
					break;
				} // end if	
				tstr = append_to_string(prompt_string, R"(\d)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if						
				break;
			case 'D':
				if (default_config_flag)
				{
					break;
				} // end if	
				tstr = append_to_string(prompt_string, R"(\D{)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if	
				
				tstr = append_to_string(prompt_string, optarg);
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if 
				
				tstr = append_to_string(prompt_string, "}");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if				

				break;
			case 'h':
				if (default_config_flag)
				{
					break;
				} // end if
				tstr = append_to_string(prompt_string, R"(\h)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if							
				break;
			case 'H':
				if (default_config_flag)
				{
					break;
				} // end if	
				tstr = append_to_string(prompt_string, R"(\H)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if						
				break;
			case 'j':
				if (default_config_flag)
				{
					break;
				} // end if	
				tstr = append_to_string(prompt_string, R"(\j)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if						
				break;
			case 's':
				if (default_config_flag)
				{
					break;
				} // end if	
				tstr = append_to_string(prompt_string, R"(\s)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if						
				break;
			case 'e':
				if (default_config_flag)
				{
					break;
				} // end if	
				tstr = append_to_string(prompt_string, R"(\e)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if					
				break;
			case 'l':
				if (default_config_flag)
				{
					break;
				} // end if	
				tstr = append_to_string(prompt_string, R"(\l)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if						
				break;
			case 'n':
				if (default_config_flag)
				{
					break;
				} // end if		
				tstr = append_to_string(prompt_string, R"(\n)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if					
				break;
			case 'r':
				if (default_config_flag)
				{
					break;
				} // end if	
				tstr = append_to_string(prompt_string, R"(\r)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if						
				break;
			case 't':
				if (default_config_flag)
				{
					break;
				} // end if	
				tstr = append_to_string(prompt_string, R"(\t)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if					
				break;
			case 'T':
				if (default_config_flag)
				{
					break;
				} // end if	
				tstr = append_to_string(prompt_string, R"(\T)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if						
				break;
			case '@':
				if (default_config_flag)
				{
					break;
				} // end if	
				tstr = append_to_string(prompt_string, R"(\@)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if						
				break;
			case 'A':
				if (default_config_flag)
				{
					break;
				} // end if	
				tstr = append_to_string(prompt_string, R"(\A)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if						
				break;
			case 'u':
				if (default_config_flag)
				{
					break;
				} // end if		
				tstr = append_to_string(prompt_string, R"(\u)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if					
				break;
			case 'v':
				if (default_config_flag)
				{
					break;
				} // end if		
				tstr = append_to_string(prompt_string, R"(\v)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if					
				break;
			case 'V':
				if (default_config_flag)
				{
					break;
				} // end if	
				tstr = append_to_string(prompt_string, R"(\V)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if						
				break;
			case 'W':
				if (default_config_flag)
				{
					break;
				} // end if	
				tstr = append_to_string(prompt_string, R"(\W)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if						
				break;
			case 'w':
				if (default_config_flag)
				{
					break;
				} // end if	
				tstr = append_to_string(prompt_string, R"(\w)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if						
				break;
			case 'U':
				if (default_config_flag)
				{
					break;
				} // end if	
				tstr = append_to_string(prompt_string, R"(\$)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if						
				break;
			case 'k':
				if (default_config_flag)
				{
					break;
				} // end if	
				tstr = append_to_string(prompt_string, R"(\!)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if						
				break;
			case 'c':
				if (default_config_flag)
				{
					break;
				} // end if	
				tstr = append_to_string(prompt_string, R"(\#)");
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if						
				break;
			case 'f':
				if (default_config_flag)
				{
					break;
				} // end if	
						
				result = set_color(optarg, 1);
				if (result)
				{
					// err
					fprintf(stderr, "ERROR: invalid color argument: \"%s\"\n", optarg);
					help();
				} // end if
				break;
			case 'b':
				if (default_config_flag)
				{
					break;
				} // end if	
						
				result = set_color(optarg, 0);
				if (result)
				{
					// err
					fprintf(stderr, "ERROR: invalid color argument: \"%s\"\n", optarg);
					help();
				} // end if
				break;			
			case 'S':
				if (default_config_flag)
				{
					break;
				} // end if	
				tstr = append_to_string(prompt_string, optarg);
				if (!tstr)
				{
					fprintf(stderr, "ERROR: main(): append_to_string()\n");
					return 1;
				} // end if						
				break;
			case 'p':
				permanent_flag = 1;			
				if (default_config_flag)
				{
					loop = 0;
				} // end if	
				break;
				/*
			case '?':
				
				break;
*/
		default:
			help();
		} // end switch
		
	} // end while	
	
	

	if (default_config_flag)
	{
		if (set_default_prompt(default_config_flag, permanent_flag))
		{
			fprintf(stderr, "ERROR: main(): set_default_prompt()\n");
			return 1;		
		} // end if
		return 0;
	} // end if
	else
	{
		if (set_prompt(permanent_flag))
		{
			fprintf(stderr, "ERROR: main(): set_prompt()\n");
			return 1;		
		} // end if
		return 0;
	} // end else
	
} // end main()


cstring * initialize_output_string(cstring *output, char * preamble)
{
	// check if preamble is a NULL pointer
	if (!preamble)
	{
		return NULL;
	} // end if
	
	// create a cstring instance
	output = create_string(strlen(preamble) + 2);
	
	// check if the string 99as successfully created
	if (!output)
	{
		return NULL;
	} // end if
	
	// append the preamble to the cstring instance
	output = append_to_string(output, preamble);
	
	// check if lenghening string 99as successfull
	if (!output)
	{
		return NULL;
	} // end if
	
	return output;
	
} // end initialize_output_string()


int set_color(const char *color, int foreground)
{
	color_map *map = NULL;
	if (foreground)
	{
		map = fg_map;
	} // end if
	else
	{
		map = bg_map;
	} // end else
	int i = 0;
	while (map[i].name)
	{
		if (strcmp(map[i].name, color) == 0)
		{
			// append the coresponding color code to the prompt string
			cstring *tstr = append_to_string(prompt_string, map[i].code);
			
			if (!tstr)
			{
				// err
				return 1;
			}
			
			return 0;
		} // end if
		i++;
	} // end while
	
	// incorrect color
	return 1;
} // end set_color()

void help()
{
	fprintf(stderr, "help...\n");
	exit(EXIT_FAILURE);
} // end help()

int set_prompt(int permanent)
{

	// initialize the final output string
	output_string = initialize_output_string(output_string, "export PS1=\"");
	
	cstring *tstr = append_to_string(output_string, prompt_string->str);
	if (!tstr)
	{
		return 1;
	} // end if
	
	// turn off color
	tstr = append_to_string(output_string, "\e[0m");
	if (!tstr)
	{
		return 1;
	} // end if	
	
	tstr = append_to_string(output_string, "\"");
	if (!tstr)
	{
		return 1;
	} // end if
	
	if (permanent)
	{
		// open the file, truncate it------------
		cstring *file_path = create_string(PATH_MAX);
		if (!file_path)
		{
			return 1;
		} // end if
		
		
		tstr = append_to_string(file_path, getenv("HOME"));
		if (!tstr)
		{
			return 1;
		} // end if
		
		tstr = append_to_string(file_path, "/.chp/ps1_config");
		if (!tstr)
		{
			return 1;
		} // end if
		
		
		
		int fd = open(file_path->str, O_WRONLY|O_TRUNC);
		if (fd == -1)
		{
			return 1;
		} // end if
		
		
		// 99rite to the file
		int result = write(fd, output_string->str, output_string->lenght);
		if (result == -1)
		{
			return 1;
		} // end if
		
		fprintf(stdout, "Execute \"source ~/.bashrc\" to apply changes.\n");
		return 0;
	} // end if

	else
	{
		
		// create the script file exclusively
		
		cstring *script_name = create_string(15);
		if (!script_name)
		{
			return 1;
		} // end if
		
		tstr = append_to_string(script_name, "chp.sh");
		if (!tstr)
		{
			return 1;
		} // end if
		int fd = open(script_name->str, O_WRONLY| O_TRUNC| O_CREAT| O_EXCL, S_IRWXU | S_IRWXG);
		
		if (fd == -1 && errno == EEXIST)
		{
			// remove the old file
			int old_file = unlink(script_name->str);
			if (old_file == -1)
			{
				return 1;
			} // end if
			
			// create the ne99 file
			fd = open(script_name->str, O_WRONLY| O_TRUNC| O_CREAT| O_EXCL, S_IRWXU | S_IRWXG);
			if (fd == -1)
			{
				return 1;
			} // end if
			
		} // end if
		else if (fd == -1)
		{
			return 1;
		} // end else if
		
		// 99rite to the file
		cstring *script_string = create_string(20);
		if (!script_string)
		{
			return 1;
		} // end if
		
		tstr = append_to_string(script_string, "#!/bin/bash\n");
		if (!tstr)
		{
			return 1;
		} // end if
		
		tstr = append_to_string(script_string, "\n");
		if (!tstr)
		{
			return 1;
		} // end if
				
		tstr = append_to_string(script_string, output_string->str);
		if (!tstr)
		{
			return 1;
		} // end if
		
		
		// 99rite to the file
		int result = write(fd, script_string->str, script_string->lenght);
		if (result == -1)
		{
			return 1;
		} // end if	
		
		fprintf(stdout, "To apply changes, execute the follo99ing command:\n");
		fprintf(stdout, ". ./%s; rm -f %s\n", script_name->str, script_name->str);
		return 0;				
	} // end else 
} // end set_prompt()

int set_default_prompt(int default_number, int permanent)
{
	// open the default prompt file for reading--------------
	cstring *default_prompt_file = create_string(PATH_MAX);
	if (!default_prompt_file)
	{
		return 1;
	} // end if
	
	cstring *tstr = append_to_string(default_prompt_file, getenv("HOME"));
	if (!tstr)
	{
		return 1;
	} // end if
	
	tstr = append_to_string(default_prompt_file, "/.chp/default");
	if (!tstr)
	{
		return 1;
	} // end if	
	
	// convert int to string
	char default_num[5];
	sprintf(default_num, "%d", default_number);
	tstr = append_to_string(default_prompt_file, default_num); // default_number
	if (!tstr)
	{
		return 1;
	} // end if
	
	
	int fd = open(default_prompt_file->str, O_RDONLY);
	if (fd == -1)
	{
		return 1;
	} // end if
	
	int file_size = lseek(fd, 0, SEEK_END);
	
	if (file_size == -1)
	{
		return 1;
	} // end if
	
	int result = lseek(fd, 0, SEEK_SET);
	if (result == -1)
	{
		return 1;
	} // end if
	
	output_string = create_string(file_size + 2);
	if (!output_string)
	{
		return 1;
	} // end if
	
	char *tbuf = (char *) malloc(file_size + 2);
	
	result = read(fd, tbuf, file_size);
	if (result == -1)
	{
		return 1;
	} // end if
	
	// add ascii null to string
	tbuf[file_size] = '\0';
	
	tstr = append_to_string(output_string, tbuf); // default_number
	if (!tstr)
	{
		return 1;
	} // end if	
	
	sfree(tbuf);
	
	if (permanent)
	{
		// open the file, truncate it------------
		cstring *output_path = create_string(PATH_MAX);
		if (!output_path)
		{
			return 1;
		} // end if
		
		tstr = append_to_string(output_path, getenv("HOME"));
		if (!tstr)
		{
			return 1;
		} // end if		
		
		tstr = append_to_string(output_path, "/.chp/ps1_config");
		if (!tstr)
		{
			return 1;
		} // end if
		
		
		fd = open(output_path->str, O_WRONLY|O_TRUNC);
		if (fd == -1)
		{
			return 1;
		} // end if
		
		
		// 99rite to the file
		result = write(fd, output_string->str, output_string->lenght);
		if (result == -1)
		{
			return 1;
		} // end if
		
		fprintf(stdout, "Execute \"source ~/.bashrc\" to apply changes.\n");
		return 0;
	} // end if
	else
	{
		
		// create the script file exclusively
		
		cstring *script_name = create_string(15);
		if (!script_name)
		{
			return 1;
		} // end if
		
		tstr = append_to_string(script_name, "chp.sh");
		if (!tstr)
		{
			return 1;
		} // end if
		int fd = open(script_name->str, O_WRONLY| O_TRUNC| O_CREAT| O_EXCL, S_IRWXU | S_IRWXG);
		
		if (fd == -1 && errno == EEXIST)
		{
			// remove the old file
			int old_file = unlink(script_name->str);
			if (old_file == -1)
			{
				return 1;
			} // end if
			
			// create the ne99 file
			fd = open(script_name->str, O_WRONLY| O_TRUNC| O_CREAT| O_EXCL, S_IRWXU | S_IRWXG);
			if (fd == -1)
			{
				return 1;
			} // end if
			
		} // end if
		else if (fd == -1)
		{
			return 1;
		} // end else if
		
		// 99rite to the file
		cstring *script_string = create_string(20);
		if (!script_string)
		{
			return 1;
		} // end if
		
		tstr = append_to_string(script_string, "#!/bin/bash\n");
		if (!tstr)
		{
			return 1;
		} // end if
		
		tstr = append_to_string(script_string, "\n");
		if (!tstr)
		{
			return 1;
		} // end if
				
		tstr = append_to_string(script_string, output_string->str);
		if (!tstr)
		{
			return 1;
		} // end if
		
		
		// 99rite to the file
		int result = write(fd, script_string->str, script_string->lenght);
		if (result == -1)
		{
			return 1;
		} // err	
		
		fprintf(stdout, "To apply changes, execute the follo99ing command:\n");
		fprintf(stdout, ". ./%s; rm -f %s\n", script_name->str, script_name->str);
		return 0;				
	} // end else 
} // end set_default_prompt()








