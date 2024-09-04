/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hrdc_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:36:08 by svalchuk          #+#    #+#             */
/*   Updated: 2024/09/04 18:37:22 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	ft_count_heredocs(t_mhell *mhell);
static char	*ft_create(int i);

bool	ft_create_files(t_mhell *mhell, char **hrdc)
{
	int	nb;
	int	i;

	i = 0;
	nb = ft_count_heredocs(mhell);
	if (nb == 0)
		return (true);
	hrdc = ft_calloc(nb + 1, sizeof(char *));
	if (!hrdc)
		return (printf(ER ER_ALLOC), false);
	while (i < nb)
	{
		hrdc[i] = ft_create(i);
		if (!hrdc[i])
			return (false);
		i++;
	}
	return (true);
}

static int	ft_count_heredocs(t_mhell *mhell)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (i < mhell->tkn_l)
	{
		if (mhell->tkn[i].type == _hrdc)
			nb++;
		i++;
	}
	return (nb);
}

static char	*ft_create(int i)
{
	char	*file_nb;
	char	*hrdc_file;

	hrdc_file = NULL;
	file_nb = ft_itoa(i);
	if (!file_nb)
		return (printf(ER ER_ALLOC), NULL);
	hrdc_file = ft_strjoin("heredocs/.heredoc_", file_nb);
	ft_free(file_nb);
	if (!hrdc_file)
		return (printf(ER ER_ALLOC), NULL);
	return (hrdc_file);
}

void	ft_delete_heredoc_files(char **heredoc_files)
{
	int	i;

	i = 0;
	if (!heredoc_files)
		return ;
	while (heredoc_files[i])
	{
		unlink(heredoc_files[i]);
		i++;
	}
}
