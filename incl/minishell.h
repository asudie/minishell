#ifndef MINISHELL_H
# define MINISHELL_H

# include "../ft_destructor/ft_alloc.h"
# include "../libft/libft.h"
#include "../42_pipex/incl/pipex.h"
#include "../42_pipex/ft_printf/ft_printf.h"
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
	char			**args;	// An array of command arguments, e.g., ["ls", "-l", NULL]
	char			*in_rd;	// Input redirection file, e.g., "input.txt"
	char			*out_rd;// Output redirection file, e.g., "output.txt"
	int				append;	// Flag for append mode (1 for >>, 0 for >)
	// HERE-DOC
	char 			**envp;
	struct s_cmd	*next;	// Pointer to the next command in case of pipes
}	t_cmd;

// PARSER
void	ft_parsing(t_cmd *cmd, char *input);

// EXECUTOR
int out_rd(t_cmd *cmd);
int in_rd(t_cmd *cmd);
int print_file_by_fd(int fd);
int	execute_builtin(t_cmd *cmd);
int start_exec(t_cmd *cmd);

// PIPEX
void	ft_validate_cmd(char **argv);
void	ft_validate_file(char **argv);
void	ft_error_output(char *path, char *msg, int code);
void	ft_free_array(char **array);
char	*ft_find_path(char *cmd, char *path);
char	**ft_separate(char *a, char d);

// UTILITY
int	ft_strcmp(char *s1, char *s2);

#endif