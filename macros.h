#ifndef HELPERS_H
#define HELPERS_H

/* Include Guards Convention */
#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

/* Prompt to be printed */
#define PROMPT_MSG "$"

/* Resume from the unused attribute */
#define UNUSED __attribute__((unused))

/* Buffer size for each read call in _getline */
#define BUFFER_SIZE 1024

/************* FORMATTED STRING FOR HELP BUILT-IN **************/

#define HELP_CD_MSG "cd=\n"\
"cd:\tcd [dir]\n\n"\
"	Change the shell working directory.\n\n"\
"	If no argument is given to cd, the command will be interpreted\n"\
"	as cd $HOME.\n"\
"	If the argument is -, the command will be interpreted\n"\
"	as cd $OLDPWD.\n\n"

// (rest of the formatted strings)

#define HELP_MSG "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\
"	Display information about builtin commands.\n\n"\
"	Displays brief summaries of builtin commands.  If BUILTIN_NAME is\n"\
"	specified, gives detailed help on all commands matching BUILTIN_NAME,\n"\
"	otherwise the list of help topics is printed. BUILTIN_NAME list.\n"\
"	Arguments:\n\n"\
"	BUILTIN_NAME specifiying a help topic.\n\n"\
"	cd\t[dir]\n"\
"	exit\t[status]\n"\
"	env\n"\
"	setenv\t[variable value]\n"\
"	unset\t[variable]\n"\
"	help\t[built_name]\n\n"

#endif /* HELPERS_H_INCLUDED */
#endif /* HELPERS_H */
