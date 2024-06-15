/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:06:47 by svalchuk          #+#    #+#             */
/*   Updated: 2024/06/15 20:49:10 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_cmd
{
	char				*cmd;		// The command name, e.g., "ls"
	char				**args;		// An array of arguments, e.g., ["ls", "-l", NULL]
	char				*in_rd;		// Input redirection file, e.g., "input.txt"
	char				*out_rd;	// Output redirection file, e.g., "output.txt"
	int					append;		// Flag for append mode (1 for >>, 0 for >)
	struct s_cmd		*next;		// Pointer to the next command in case of pipes
}	t_cmd;

#endif