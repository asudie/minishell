/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c		                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:22:44 by ******           #+#    #+#              */
/*   Updated: 2024/07/22 00:43:38 by ******           ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	resolve_full_path(t_cmd *cmd, char **full_path)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	path = NULL;
	if (access(cmd->args[0], X_OK) == 0)
		return (*full_path = cmd->args[0], 0);
	path = get_env_var(cmd->envp, "PATH");
	if (!path)
		return (1);
	paths = ft_split(path + 5, ':');
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		*full_path = ft_strjoin(tmp, cmd->args[0]);
		free(tmp);
		if (access(*full_path, X_OK) == 0)
			return (ft_free_array(paths), 0);
		free(*full_path);
		i++;
	}
	ft_free_array(paths);
	return (1);
}
