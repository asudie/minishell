/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c		                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:22:44 by ******           #+#    #+#              */
/*   Updated: 2024/07/22 00:43:38 by ******           ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	is_valid_n_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	print_arguments(char **args, int start)
{
	int	i;

	i = start;
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
}

int	custom(t_cmd *cmd)
{
	char	*full_path;

	if (resolve_full_path(cmd, &full_path) == 1)
	{
		ft_printf("Command not found: %s\n", cmd->args[0]);
		return (127);
	}
	if (execve(full_path, cmd->args, cmd->envp) == 1)
	{
		free(full_path);
		perror("execve");
		return (1);
	}
	free(full_path);
	return (0);
}
