/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:22:44 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/19 15:03:48 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

bool	ft_input_parse(t_cmd **cmd, char *input)
{
	char	*cmd_line;

	(void)cmd;
	while (*input)
	{
		ft_skip_spaces(&input);
		cmd_line = input;
		// ft_find_next_cmd(cmd, &input, &cmd_line);
	}
	return (false);
}

// static int	ft_find_next_cmd(t_cmd **cmd, char **str, char **cmd_line)
// {
// 	while (*str)
// 	{
		
// 	}
// 	return (0);
// }















// static void	ft_replace_pipes(char *str, char delimiter);
// static void	ft_restore_pipes(char **cmd);

// int	ft_input_parse(t_mhell *mhell, char *input)
// {
// 	char	**cmd;
	
// 	(void)mhell;
// 	ft_replace_pipes(input, '"');
// 	ft_replace_pipes(input, '\'');
// 	cmd = ft_split(input, '|');
// 	ft_restore_pipes(cmd);
// 	for (int i = 0; cmd[i]; i++)
// 		printf("cmd[%i]: %s\n", i, cmd[i]);
// 	// ft_put_in_struct(mhell->cmd, cmd);
// 	return (0);
// }

// static void	ft_replace_pipes(char *str, char delimiter)
// {
// 	while (*str && *str != delimiter)
// 		str++;
// 	if (*str)
// 		str++;
// 	while (*str && *str != delimiter)
// 	{
// 		if (*str == '|')
// 			*str = -1;
// 		str++;
// 	}
// 	if (*str)
// 		str++;
// 	if (*str)
// 		ft_replace_pipes(str, delimiter);
// }

// static void	ft_restore_pipes(char **cmd)
// {
// 	char	*str;

// 	while (*cmd)
// 	{
// 		str = *cmd;
// 		while (*str)
// 		{
// 			if (*str == -1)
// 				*str = '|';
// 			str++;
// 		}
// 		cmd++;
// 	}
// 	return ;
// }

// // static void ft_put_in_struct(t_cmd *cmd, char **cmd_line)
// // {	
// // }
