/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:26:38 by svalchuk          #+#    #+#             */
/*   Updated: 2024/06/05 21:10:35 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

void	ft_error_output(char *path, char *msg, int code)
{
	write(2, COLOR_RED"pipex: "COLOR_RESET, 18);
	if (path == NULL)
	{
		write(2, COLOR_BLUE, ft_strlen(COLOR_BLUE));
		write(2, msg, ft_strlen(msg));
		write(2, COLOR_RESET, ft_strlen(COLOR_RESET));
		exit(1);
	}
	write(2, COLOR_YELLOW, ft_strlen(COLOR_YELLOW));
	write(2, path, ft_strlen(path));
	write(2, ": ", 2);
	write(2, COLOR_RESET, ft_strlen(COLOR_RESET));
	write(2, COLOR_BLUE, ft_strlen(COLOR_BLUE));
	write(2, msg, ft_strlen(msg));
	write(2, COLOR_RESET, ft_strlen(COLOR_RESET));
	exit(code);
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*ft_find_path(char *cmd, char *path)
{
	char	**paths;
	char	*tmp;
	char	*res;
	int		fd;
	int		i;

	i = 0;
	paths = ft_split(path + 5, ':');
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		res = ft_strjoin(tmp, cmd);
		free(tmp);
		fd = open(res, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			ft_free_array(paths);
			return (res);
		}
		free(res);
		i++;
	}
	ft_free_array(paths);
	return (NULL);
}

void	ft_validate_file(char **argv)
{
	if (ft_strlen(argv[1]) == 0 || argv[1] == NULL)
		ft_error_output(NULL, "Invalid file name\n", 1);
	if (argv[1][0] == ' ' && argv[1][1] == '\0')
		ft_error_output(NULL, "Invalid file name\n", 1);
	if (ft_strlen(argv[4]) == 0 || argv[4] == NULL)
		ft_error_output(NULL, "Invalid file name\n", 1);
	if (argv[4][0] == ' ' && argv[4][1] == '\0')
		ft_error_output(NULL, "Invalid file name\n", 1);
}

void	ft_validate_cmd(char **argv)
{
	if (ft_strlen(argv[2]) == 0 || argv[2] == NULL)
		ft_error_output(NULL, "Invalid command\n", 1);
	if (argv[2][0] == ' ' && argv[2][1] == '\0')
		ft_error_output(NULL, "Invalid command\n", 1);
	if (ft_strlen(argv[3]) == 0 || argv[3] == NULL)
		ft_error_output(NULL, "Invalid command\n", 1);
	if (argv[3][0] == ' ' && argv[3][1] == '\0')
		ft_error_output(NULL, "Invalid command\n", 1);
}
