/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:19:21 by svalchuk          #+#    #+#             */
/*   Updated: 2024/06/05 18:08:55 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../ft_printf/ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>

# define COLOR_RESET "\033[0m"
# define COLOR_RED "\033[1;31m"
# define COLOR_GREEN "\033[1;32m"
# define COLOR_YELLOW "\033[1;33m"
# define COLOR_BLUE "\033[1;34m"
# define COLOR_PURPLE "\033[1;35m"
# define COLOR_CYAN "\033[1;36m"

typedef struct s_pipex
{
	char	**cmd1;
	char	*input_file;
	char	*output_file;
	char	**cmd2;
	char	*path;
	char	*path1;
	char	*path2;
	char	**envp;
}	t_pipex;

void	ft_validate_cmd(char **argv);
void	ft_validate_file(char **argv);
void	ft_error_output(char *path, char *msg, int code);
void	ft_free_array(char **array);
char	*ft_find_path(char *cmd, char *path);
char	**ft_separate(char *a, char d);

#endif