/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:11:40 by svalchuk          #+#    #+#             */
/*   Updated: 2024/08/19 15:15:09 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_print_tkn(t_mhell *mhell)
{
	int	i = 0;
	while (i < mhell->tkn_l)
	{
		printf("Token: %s\tType: %d\n", mhell->tkn[i].token, mhell->tkn[i].type);
		i++;
	}
}

void	ft_print_cmd(t_cmd *cmd)
{
	printf("\n");
	for (int i = 0; cmd->args[i]; i++)
			printf("args[%i]: %s\n", i, cmd->args[i]);
	printf("rdin: %s\n", cmd->in_rd);
	printf("rdout: %s\n", cmd->out_rd);
	printf("append: %i\n", cmd->append);
	printf("heredoc: %i\n", cmd->heredoc);
}

void	ft_prep_cmd(t_mhell *mhell);
void	ft_init_cmd(t_mhell *mhell, int *i, t_cmd *cmd);
void	ft_alloc_cmd(int args, int in, int out, t_cmd	*cmd);

void	ft_create_cmd(t_mhell *mhell)
{
	ft_print_tkn(mhell);
	t_cmd	*cmd;
	int	i;

	i = 0;
	ft_prep_cmd(mhell);
	cmd = mhell->cmd;
	while (mhell->tkn)
	{
		printf("here\n");
		if (mhell->tkn[i].type == _pipe)
			cmd = cmd->next;
		else if (mhell->tkn[i].type == _rdin || mhell->tkn[i].type == _hrdc)
		{
			if (mhell->tkn[i].type == _hrdc)
				cmd->heredoc = 1;
			i++;
			cmd->in_rd = ft_strdup(mhell->tkn[i].token);
		}
		else if (mhell->tkn[i].type == _rdout || mhell->tkn[i].type == _append)
		{
			if (mhell->tkn[i].type == _append)
				cmd->append = 1;
			i++;
			cmd->out_rd = ft_strdup(mhell->tkn[i].token);
		}
		else
		{
			cmd->args[i] = mhell->tkn[i].token;
			printf("here\n");
			i++;
		}
		i++;
	}
	mhell->cmd = cmd;
}

void	ft_prep_cmd(t_mhell *mhell)
{
	t_cmd *cmd;
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (i < mhell->tkn_l)
	{
		if (mhell->tkn[i].type == _pipe)
			len++;
		i++;
	}
	mhell->cmd = ft_malloc(sizeof(t_cmd) * len);
	mhell->cmd_l = len;
	i = 0;
	len = 0;
	while (len < mhell->cmd_l && i < mhell->tkn_l)
	{
		ft_init_cmd(mhell, &i, cmd);
		i++;
		len++;
		cmd = cmd->next;
	}
	mhell->cmd = cmd;
}

void	ft_init_cmd(t_mhell *mhell, int *i, t_cmd *cmd)
{
	int	args;
	int	in;
	int	out;

	out = 0;
	in = 0;
	args = 0;
	while (mhell->tkn && *i < mhell->tkn_l && mhell->tkn[*i].token && mhell->tkn[*i].type != _pipe)
	{
		if (mhell->tkn[*i].type == _text)
			args++;
		else
		{
			if (mhell->tkn[*i].type == _rdin || mhell->tkn[*i].type == _hrdc)
			{
				(*i)++;
				in = ft_strlen(mhell->tkn[*i].token);
			}
			else if (mhell->tkn[*i].type == _rdout || mhell->tkn[*i].type == _append)
			{
				(*i)++;
				out = ft_strlen(mhell->tkn[*i].token);
			}
		}		
		(*i)++;
	}
	ft_alloc_cmd(args, in, out, cmd);
}

void	ft_alloc_cmd(int args, int in, int out, t_cmd *cmd)
{
	cmd->args = ft_malloc(sizeof(char *) * (args + 1));
	cmd->args[args] = NULL;
	cmd->in_rd = ft_malloc(sizeof(char *) * in);
	cmd->out_rd = ft_malloc(sizeof(char *) * out);
}

/*
< in ls -l | wc -c > out | cat << g | echo "Hello World!" >> out | echo "No $PWD" | echo 'Yes $SHLVL'
*/