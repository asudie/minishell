/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hrdc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:51:49 by svalchuk          #+#    #+#             */
/*   Updated: 2024/08/13 19:04:11 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_hrdc(t_mhell *mhell, int order)
{
	int	hrdc;
	int	in;
	int	i;

	i = 0;
	hrdc = 0;
	while (i++ < order)
	{
		if (mhell->tkn_l > 1 && mhell->tkn[i].type == hrdc && (i + 1) < mhell->cmd && mhell->tkn[i + 1].type == text)
			hrdc++;
	}
	if (!hrdc)
		return (0);
	// mhell->cmd = ft_malloc(sizeof(t_cmd) * 1);
	// mhell->cmd = 1;
	ft_alloc_cmd(mhell->cmd);
	i = 0;
	in = 0;
	while (i++ < order)
	{
		if (mhell->tkn[i].type == hrdc)
			ft_fill_redir(&mhell->cmd);
	}
	return (hrdc);
}
