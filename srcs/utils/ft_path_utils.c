/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:40:01 by svalchuk          #+#    #+#             */
/*   Updated: 2024/08/09 19:16:57 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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
