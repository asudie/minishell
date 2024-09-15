/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 20:12:24 by svalchuk          #+#    #+#             */
/*   Updated: 2024/09/14 17:58:38 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	ft_clear_tkn(t_tkn **tkn, int *len);

void	ft_free_mhell_data(t_mhell *mhell)
{
	if (mhell->tkn && mhell->tkn_l)
		ft_clear_tkn(&mhell->tkn, &mhell->tkn_l);
	if (mhell->cmd)
	{
		ft_cmdclear(&mhell->cmd, ft_free);
		mhell->cmd_l = 0;
	}
}

static void	ft_clear_tkn(t_tkn **tkn, int *len)
{
	int	i;

	i = 0;
	while (i < *len && (*tkn)[i].token)
	{
		ft_free((*tkn)[i].token);
		i++;
	}
	if (*len)
		ft_free(*tkn);
	*tkn = NULL;
	*len = 0;
}
