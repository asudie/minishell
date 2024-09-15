/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:11:40 by svalchuk          #+#    #+#             */
/*   Updated: 2024/09/15 14:38:12 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/* void	ft_print_tkn(t_mhell *mhell)
{
	int	i;

	i = 0;
	while (i < mhell->tkn_l)
	{
	printf("Token: %s\tType: %d\n", mhell->tkn[i].token, mhell->tkn[i].type);
		i++;
	}
} */

/* void	ft_print_cmd(t_cmd *cmd)
{
	t_cmd *tmp = cmd;
	while (tmp)
	{
		printf("\n");
		for (int i = 0; tmp->args[i]; i++)
				printf("args[%i]: %s\n", i, tmp->args[i]);
		printf("rdin: %s\n", tmp->in_rd);
		printf("rdout: %s\n", tmp->out_rd);
		printf("append: %i\n", tmp->append);
		printf("heredoc: %i\n", tmp->heredoc);
		tmp = tmp->next;
	}
} */

void		ft_fill_cmd(t_mhell *mhell, int *i, t_cmd *cmd);
static void	ft_process_token(t_mhell *mhell, int *i,
				t_cmd_alloc *allocs, int *j);
t_cmd		*ft_allocate_cmd(t_cmd_alloc *allocs);

void	ft_create_cmd(t_mhell *mhell)
{
	t_cmd	*cmd;
	int		len;
	int		i;

	i = 0;
	len = -1;
	cmd = NULL;
	while (i < mhell->tkn_l)
	{
		if (mhell->tkn[i].type == _pipe)
			mhell->cmd_l++;
		i++;
	}
	i = 0;
	while (++len <= mhell->cmd_l)
	{
		ft_fill_cmd(mhell, &i, cmd);
		i++;
	}
}

void	ft_fill_cmd(t_mhell *mhell, int *i, t_cmd *cmd)
{
	t_cmd_alloc	*allocs;
	int			j;

	j = -1;
	allocs = ft_calloc(1, sizeof(t_cmd_alloc));
	allocs->args = ft_calloc(mhell->tkn_l, sizeof(char *));
	while (*i < mhell->tkn_l && mhell->tkn[*i].type != _pipe)
	{
		ft_process_token(mhell, i, allocs, &j);
	}
	cmd = ft_allocate_cmd(allocs);
	ft_cmdadd_back(&mhell->cmd, cmd);
}

static void	ft_process_token(t_mhell *mhell, int *i,
					t_cmd_alloc *allocs, int *j)
{
	if (mhell->tkn[*i].type == _rdin || mhell->tkn[*i].type == _hrdc)
	{
		if (mhell->tkn[*i].type == _hrdc)
			allocs->heredoc = 1;
		(*i)++;
		allocs->in_rd = ft_strdup(mhell->tkn[*i].token);
	}
	else if (mhell->tkn[*i].type == _rdout || mhell->tkn[*i].type == _append)
	{
		if (mhell->tkn[*i].type == _append)
			allocs->append = 1;
		(*i)++;
		allocs->out_rd = ft_strdup(mhell->tkn[*i].token);
	}
	else
	{
		allocs->num_args++;
		allocs->args[++(*j)] = ft_strdup(mhell->tkn[*i].token);
	}
	(*i)++;
}
