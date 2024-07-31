/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:22:44 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/31 16:00:30 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

bool	ft_input_parse(t_mhell *mhell, char *input)
{
	char	*cmd_line;

	(void)mhell;
	while (*input)
	{
		ft_skip_spaces(&input);
		cmd_line = input;
		// ft_find_next_cmd(cmd, &input, &cmd_line);
	}
	return (true);
}
