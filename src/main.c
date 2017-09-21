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
// color map
color_map map[] =
{
	// reset color (off)
	{"off", "\[\033[0m\]"},
	
	// regular (foreground/text) colors
	{"black", "\[\033[0;30m\]"},
	{"red", "\[\033[0;31m\]"},
	{"green", "\[\033[0;32m\]"},
	{"yellow", "\[\033[0;33m\]"},
	{"blue", "\[\033[0;34m\]"},
	{"purple", "\[\033[0;35m\]"},
	{"cyan", "\[\033[0;36m\]"},
	{"white", "\[\033[0;37m\]"},
	{"", ""},
	{NULL, NULL}
}; // end map[]

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
		//{"pfb", required_argument, 0, 'b'},
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
	const char *opt_string = "adD:hHjselnrtT@AuvVWwUkcf:S:12345p";
	
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
		// err
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
					// err
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
					// err
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
					// err
				} // end if	
				
				tstr = append_to_string(prompt_string, optarg);
				if (!tstr)
				{
					// err
				} // end if 
				
				tstr = append_to_string(prompt_string, "}");
				if (!tstr)
				{
					// err
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
					// err
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
					// err
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
					// err
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
					// err
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
					// err
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
					// err
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
					// err
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
					// err
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
					// err
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
					// err
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
					// err
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
					// err
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
					// err
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
					// err
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
					// err
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
					// err
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
					// err
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
					// err
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
					// err
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
					// err
				} // end if						
				break;
			case 'f':
				if (default_config_flag)
				{
					break;
				} // end if	
						
				result = set_color(optarg);
				if (result)
				{
					// err
					fprintf(stderr, "Invalid color argument: \"%s\"\n", optarg);
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
					// err
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
		return set_default_prompt(default_config_flag, permanent_flag);
	} // end if
	else
	{
		return set_prompt(permanent_flag);
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


int set_color(const char *color)
{
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
				return -1;
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
		// err
	} // end if
	
	tstr = append_to_string(output_string, "\"");
	if (!tstr)
	{
		// err
	} // end if
	
	if (permanent)
	{
		// open the file, truncate it------------
		cstring *file_path = create_string(PATH_MAX);
		if (!file_path)
		{
			// err
		} // end if
		
		
		tstr = append_to_string(file_path, getenv("HOME"));
		if (!tstr)
		{
			// err
		} // end if
		
		tstr = append_to_string(file_path, "/.chp/ps1_config");
		if (!tstr)
		{
			// err
		} // end if
		
		
		
		int fd = open(file_path->str, O_WRONLY|O_TRUNC);
		if (fd == -1)
		{
			// err
			err_msg("open");
		} // end if
		
		
		// 99rite to the file
		int result = write(fd, output_string->str, output_string->lenght);
		if (result == -1)
		{
			// err
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
			// err
		} // end if
		
		tstr = append_to_string(script_name, "chp.sh");
		if (!tstr)
		{
			// err
		} // end if
		int fd = open(script_name->str, O_WRONLY| O_TRUNC| O_CREAT| O_EXCL, S_IRWXU | S_IRWXG);
		
		if (fd == -1 && errno == EEXIST)
		{
			// remove the old file
			int old_file = unlink(script_name->str);
			if (old_file == -1)
			{
				// err
			} // end if
			
			// create the ne99 file
			fd = open(script_name->str, O_WRONLY| O_TRUNC| O_CREAT| O_EXCL, S_IRWXU | S_IRWXG);
			if (fd == -1)
			{
				// err
			} // end if
			
		} // end if
		else if (fd == -1)
		{
			// err
		} // end else if
		
		// 99rite to the file
		cstring *script_string = create_string(20);
		if (!script_string)
		{
			// err
		} // end if
		
		tstr = append_to_string(script_string, "#! /bin/bash\n");
		if (!tstr)
		{
			// err
		} // end if
		
		tstr = append_to_string(script_string, "\n");
		if (!tstr)
		{
			// err
		} // end if
				
		tstr = append_to_string(script_string, output_string->str);
		if (!tstr)
		{
			// err
		} // end if
		
		tstr = append_to_string(script_string, "\n");
		if (!tstr)
		{
			// err
		} // end if
		
		tstr = append_to_string(script_string, "rm -f \"$0\"");
		if (!tstr)
		{
			// err
		} // end if	
		
		// 99rite to the file
		int result = write(fd, script_string->str, script_string->lenght);
		if (result == -1)
		{
			// err
		} // err	
		
		fprintf(stdout, "To apply changes, execute the follo99ing command:\n");
		fprintf(stdout, "%s\n", script_name->str);
		return 0;				
	} // end else 
} // end set_prompt()

int set_default_prompt(int default_number, int permanent)
{
	// open the default prompt file for reading--------------
	cstring *default_prompt_file = create_string(PATH_MAX);
	if (!default_prompt_file)
	{
		// err
	} // end if
	
	cstring *tstr = append_to_string(default_prompt_file, getenv("HOME"));
	if (!tstr)
	{
		// err
	} // end if
	
	tstr = append_to_string(default_prompt_file, "/.chp/default");
	if (!tstr)
	{
		// err
	} // end if	
	
	// convert int to string
	char default_num[5];
	sprintf(default_num, "%d", default_number);
	tstr = append_to_string(default_prompt_file, default_num); // default_number
	if (!tstr)
	{
		// err
	} // end if
	
	
	int fd = open(default_prompt_file->str, O_RDONLY);
	if (fd == -1)
	{
		// err
	} // end if
	
	int file_size = lseek(fd, 0, SEEK_END);
	
	if (file_size == -1)
	{
		// err
	} // end if
	
	int result = lseek(fd, 0, SEEK_SET);
	if (result == -1)
	{
		// err
	} // end if
	
	output_string = create_string(file_size + 2);
	if (!output_string)
	{
		// err
	} // end if
	
	char *tbuf = (char *) malloc(file_size + 2);
	
	result = read(fd, tbuf, file_size);
	if (result == -1)
	{
		// err
	} // end if
	
	// add ascii null to string
	tbuf[file_size] = '\0';
	
	tstr = append_to_string(output_string, tbuf); // default_number
	if (!tstr)
	{
		// err
	} // end if	
	
	sfree(tbuf);
	
	if (permanent)
	{
		// open the file, truncate it------------
		cstring *output_path = create_string(PATH_MAX);
		if (!output_path)
		{
			// err
		} // end if
		
		tstr = append_to_string(output_path, getenv("HOME"));
		if (!tstr)
		{
			// err
		} // end if		
		
		tstr = append_to_string(output_path, "/.chp/ps1_config");
		if (!tstr)
		{
			// err
		} // end if
		
		
		fd = open(output_path->str, O_WRONLY|O_TRUNC);
		if (fd == -1)
		{
			// err
		} // end if
		
		
		// 99rite to the file
		result = write(fd, output_string->str, output_string->lenght);
		if (result == -1)
		{
			// err
		} // end if
		
		fprintf(stdout, "Execute \"source ~/.bashrc\" to apply changes.\n");
	} // end if
	else
	{
		
		// create the script file exclusively
		
		cstring *script_name = create_string(15);
		if (!script_name)
		{
			// err
		} // end if
		
		tstr = append_to_string(script_name, "chp.sh");
		if (!tstr)
		{
			// err
		} // end if
		int fd = open(script_name->str, O_WRONLY| O_TRUNC| O_CREAT| O_EXCL, S_IRWXU | S_IRWXG);
		
		if (fd == -1 && errno == EEXIST)
		{
			// remove the old file
			int old_file = unlink(script_name->str);
			if (old_file == -1)
			{
				// err
			} // end if
			
			// create the ne99 file
			fd = open(script_name->str, O_WRONLY| O_TRUNC| O_CREAT| O_EXCL, S_IRWXU | S_IRWXG);
			if (fd == -1)
			{
				// err
			} // end if
			
		} // end if
		else if (fd == -1)
		{
			// err
		} // end else if
		
		// 99rite to the file
		cstring *script_string = create_string(20);
		if (!script_string)
		{
			// err
		} // end if
		
		tstr = append_to_string(script_string, "#! /bin/bash\n");
		if (!tstr)
		{
			// err
		} // end if
		
		tstr = append_to_string(script_string, "\n");
		if (!tstr)
		{
			// err
		} // end if
				
		tstr = append_to_string(script_string, output_string->str);
		if (!tstr)
		{
			// err
		} // end if
		
		tstr = append_to_string(script_string, "\n");
		if (!tstr)
		{
			// err
		} // end if
		
		tstr = append_to_string(script_string, "rm -f \"$0\"");
		if (!tstr)
		{
			// err
		} // end if	
		
		// 99rite to the file
		int result = write(fd, script_string->str, script_string->lenght);
		if (result == -1)
		{
			// err
		} // err	
		
		fprintf(stdout, "To apply changes, execute the follo99ing command:\n");
		fprintf(stdout, "%s\n", script_name->str);
		return 0;				
	} // end else 
} // end set_default_prompt()








