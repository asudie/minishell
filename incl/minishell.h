/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:22:44 by ******           #+#    #+#              */
/*   Updated: 2024/07/22 00:43:38 by ******           ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../ft_destructor/ft_alloc.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <termcap.h>  
# include <stdbool.h>
# include <signal.h>
# include <dirent.h>
# include <stdio.h>
# include <fcntl.h>

// COLORS
# define RESET		"\033[0m"
# define BLACK		"\033[1;30m"
# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define BLUE		"\033[1;34m"
# define PURPLE		"\033[1;35m"
# define CYAN		"\033[1;36m"
# define WHITE		"\033[1;37m"
# define UNDERLINE	"\033[4m"
# define CROSSED	"\033[9m"

// ERRORS
# define ER			"\033[1;31m\n  ERROR » \033[1;34m"
# define ER_MHELL	"\033[1;31mminishell: \033[1;34m"
# define ER_ARG		"Minishell can't take arguments\n\n\033[0m"
# define ER_ALLOC	"Allocation failed\n\n\033[0m"
# define ER_QUOTE_S	"single quatation is not closed\n\033[0m"
# define ER_QUOTE_D	"double quatation is not closed\n\033[0m"
# define ER_SX_CHR	"syntax error near unexpected token `%c'\n\033[0m"
# define ER_SX_STR	"syntax error near unexpected token `%s'\n\033[0m"
# define ER_TKN		"Error creating string for tokens\n\033[0m"
# define ER_HRDC	"Error creating heredocs\n\033[0m"
# define ER_HRDC_NB	"Error creating heredoc number string\n\033[0m"
# define ER_HRDC_FN	"Error creating heredoc file name\n\033[0m"
# define ER_HRDC_FK	"Error forking for heredoc\n\033[0m"

typedef struct s_env	t_env;
typedef struct s_tkn	t_tkn;
typedef struct s_cmd	t_cmd;

typedef struct s_mhell
{
	char	*cmd_line;
	int		exit_code;
	t_env	*env;
	t_tkn	*tkn;
	int		tkn_l;
	t_cmd	*cmd;
}	t_mhell;

typedef struct s_env
{
	char			*var;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef enum e_type
{
	null,
	text,
	pipe,
	hrdc,
	rdin,
	append,
	rdout,
}	t_type;

typedef struct s_tkn
{
	char	*token;
	t_type	type;
}	t_tkn;

typedef struct s_cmd
{
	char			**args;	// An array of command arguments["ls", "-l", NULL]
	char			*in_rd;	// Input redirection file, e.g., "input.txt"
	char			*out_rd;// Output redirection file, e.g., "output.txt"
	int				append;	// Flag for append mode (1 for >>, 0 for >)
	char			**heredoc;
	char			**envp;
	struct s_cmd	*next;	// Pointer to the next command in case of pipes
}	t_cmd;

// PARSER
void	ft_init_env(t_mhell *mhell, char **envp);
char	*ft_input_prompt(t_mhell *mhell);
bool	ft_input_parse(t_mhell *mhell);
void	ft_substr_dollar(t_mhell *mhell, char **str, int state);
void	ft_tokenize(t_mhell *mhell, char *str);

// EXECUTOR
int		out_rd(t_cmd *cmd);
void	print_file_by_fd(int fd);
int		execute_builtin(t_cmd *cmd);

// UTILITY
bool	ft_input_error(t_mhell *mhell, char	*input);

t_env	*ft_find_env(t_env *env, char *var);
void	ft_envadd(t_env **env, char *var, char *val);
void	ft_envclean(t_env **env);
char	*ft_envcut(char *str);

char	**ft_split_savediv(char *str, char c);
int		ft_strchr_pos(char *s, int c);

char	*ft_arrjoin(char **arr);
void	ft_free_array(char **arr);

bool	ft_is_empty(char *str);
bool	ft_is_space(char c);
void	ft_skip_spaces(char **str);
int		ft_conc_space(char curr, char next);
bool	ft_is_quote(char c);
void	ft_quote_state(int c, int *state);
int		ft_is_spec(char *str);

#endif