/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:11:40 by svalchuk          #+#    #+#             */
/*   Updated: 2024/08/15 17:01:25 by svalchuk         ###   ########.fr       */
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

static void	ft_fill_cmd(t_mhell *mhell, int cmd, int *tkn);
static void	ft_prep_cmd(t_mhell *mhell);
static void	ft_init_cmd(t_mhell *mhell, int len, int *i);

void	ft_create_cmd(t_mhell *mhell)
{
	ft_print_tkn(mhell);
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_prep_cmd(mhell);
	while (i < mhell->cmd_l)
	{
		ft_fill_cmd(mhell, i, &j);
		j++;
		i++;
	}
	
}

static void	ft_prep_cmd(t_mhell *mhell)
{
	int	len;
	int	i;

	i = 0;
	len = 1;
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
		ft_init_cmd(mhell, len, &i);
		len++;
		i++;
	}
}

static void	ft_init_cmd(t_mhell *mhell, int len, int *i)
{
	int	arg;
	int	in;
	int	out;

	arg = 0;
	in = 0;
	out = 0;
	while (mhell->tkn && *i < mhell->tkn_l && mhell->tkn[*i].token && mhell->tkn[*i].type != _pipe)
	{
		if (mhell->tkn[*i].type == _text)
			arg++;
		else
		{
			if (mhell->tkn[*i].type == _rdin || mhell->tkn[*i].type == _hrdc)
				in++;
			else if (mhell->tkn[*i].type == _rdout || mhell->tkn[*i].type == _append)
				out++;
			(*i)++;
		}
		(*i)++;
	}
	mhell->cmd[len].args = ft_malloc(sizeof(char *) * (arg + 1));
	mhell->cmd[len].in_rd = ft_malloc(sizeof(char *) * in);
	mhell->cmd[len].out_rd = ft_malloc(sizeof(char *) * out);
	mhell->cmd[len].args[arg] = NULL;
}

static void	ft_fill_cmd(t_mhell *mhell, int cmd, int *tkn)
{
	int	i;

	i = 0;
	while (*tkn < mhell->tkn_l && mhell->tkn[*tkn].type != _pipe)
	{
		if (mhell->tkn[*tkn].type == _rdin || mhell->tkn[*tkn].type == _hrdc)
		{
			if (mhell->tkn[*tkn].type == _hrdc)
				mhell->cmd[cmd].heredoc = 1;
			(*tkn)++;
			if (mhell->tkn[*tkn].type == _text)
				mhell->cmd[cmd].in_rd = ft_strdup(mhell->tkn[*tkn].token);
		}
		else if (mhell->tkn[*tkn].type == _rdout || mhell->tkn[*tkn].type == _append)
		{
			if (mhell->tkn[*tkn].type == _append)
				mhell->cmd[cmd].append = 1;
			(*tkn)++;
			if (mhell->tkn[*tkn].type == _text)
				mhell->cmd[cmd].out_rd = ft_strdup(mhell->tkn[*tkn].token);
		}
		else
		{
			mhell->cmd[cmd].args[i] = mhell->tkn[*tkn].token;
			i++;
		}
		for (int i = 0; mhell->cmd[cmd].args[i]; i++)
			printf("args[%i]: %s", i, mhell->cmd[cmd].args[i]);
		printf("rdin: %s", mhell->cmd[cmd].in_rd);
		printf("rdout: %s", mhell->cmd[cmd].out_rd);
		printf("append: %i", mhell->cmd[cmd].append);
		printf("heredoc: %i", mhell->cmd[cmd].heredoc);
		(*tkn)++;
	}
}

/*
< in ls -l | wc -c > out | cat << g | echo "Hello World!" >> out | echo "No $PWD" | echo 'Yes $SHLVL'
*/