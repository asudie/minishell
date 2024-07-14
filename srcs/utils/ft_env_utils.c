/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:40:01 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/12 14:02:02 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_free(array[i]);
		i++;
	}
	ft_free(array);
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
		ft_free(tmp);
		fd = open(res, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			ft_free_array(paths);
			return (res);
		}
		ft_free(res);
		i++;
	}
	ft_free_array(paths);
	return (NULL);
}