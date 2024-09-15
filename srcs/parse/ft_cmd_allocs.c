/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_allocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:34:53 by svalchuk          #+#    #+#             */
/*   Updated: 2024/09/15 14:46:42 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	ft_allocate_args(t_cmd *cmd, t_cmd_alloc *allocs);
static void	ft_copy_args(t_cmd *cmd, t_cmd_alloc *allocs);
static int	ft_allocate_in_out_rd(t_cmd *cmd, t_cmd_alloc *allocs);

t_cmd	*ft_allocate_cmd(t_cmd_alloc *allocs)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)ft_malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	if (!ft_allocate_args(cmd, allocs))
	{
		ft_free(cmd);
		return (NULL);
	}
	ft_copy_args(cmd, allocs);
	if (!ft_allocate_in_out_rd(cmd, allocs))
	{
		i = 0;
		while (i < allocs->num_args)
			ft_free(cmd->args[i++]);
		ft_free(cmd->args);
		ft_free(cmd);
		return (NULL);
	}
	cmd->append = allocs->append;
	cmd->heredoc = allocs->heredoc;
	cmd->next = NULL;
	return (cmd);
}

static int	ft_allocate_args(t_cmd *cmd, t_cmd_alloc *allocs)
{
	int	i;

	cmd->args = (char **)ft_malloc((allocs->num_args + 1) * sizeof(char *));
	if (!cmd->args)
		return (0);
	i = 0;
	while (i < allocs->num_args)
	{
		cmd->args[i] = (char *)ft_malloc(256 * sizeof(char));
		if (!cmd->args[i])
		{
			while (--i >= 0)
				ft_free(cmd->args[i]);
			ft_free(cmd->args);
			return (0);
		}
		i++;
	}
	cmd->args[allocs->num_args] = NULL;
	return (1);
}

static void	ft_copy_args(t_cmd *cmd, t_cmd_alloc *allocs)
{
	int	j;

	j = 0;
	while (j < allocs->num_args && allocs->args[j])
	{
		cmd->args[j] = allocs->args[j];
		j++;
	}
	cmd->args[allocs->num_args] = NULL;
}

static int	ft_allocate_in_out_rd(t_cmd *cmd, t_cmd_alloc *allocs)
{
	if (allocs->in_rd)
	{
		cmd->in_rd = ft_strdup(allocs->in_rd);
		if (!cmd->in_rd)
			return (0);
	}
	else
		cmd->in_rd = NULL;
	if (allocs->out_rd)
	{
		cmd->out_rd = ft_strdup(allocs->out_rd);
		if (!cmd->out_rd)
		{
			ft_free(cmd->in_rd);
			return (0);
		}
	}
	else
		cmd->out_rd = NULL;
	return (1);
}
