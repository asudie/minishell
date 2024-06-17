#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <termcap.h>  
# include <signal.h>
# include <dirent.h>
# include <stdio.h>
# include <fcntl.h>

# define COLOR_RESET "\033[0m"
# define COLOR_BLACK "\033[1;30m"
# define COLOR_RED "\033[1;31m"
# define COLOR_GREEN "\033[1;32m"
# define COLOR_YELLOW "\033[1;33m"
# define COLOR_BLUE "\033[1;34m"
# define COLOR_PURPLE "\033[1;35m"
# define COLOR_CYAN "\033[1;36m"
# define COLOR_WHITE "\033[1;37m"

typedef struct s_cmd
{
	char			*cmd;	// The command name, e.g., "ls"
	char			**args;	// An array of arguments, e.g., ["ls", "-l", NULL]
	char			*in_rd;	// Input redirection file, e.g., "input.txt"
	char			*out_rd;// Output redirection file, e.g., "output.txt"
	int				append;	// Flag for append mode (1 for >>, 0 for >)
	struct s_cmd	*next;	// Pointer to the next command in case of pipes
}	t_cmd;

#endif