/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:06:47 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/03 21:29:15 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_cmd
{
	char *cmd;          // The command name, e.g., "ls"
	char **args;        // An array of arguments, e.g., ["ls", "-l", NULL]
	char *in_rd;        // Input redirection file, e.g., "input.txt"
	char *out_rd;       // Output redirection file, e.g., "output.txt"
	int append;         // Flag for append mode (1 for >>, 0 for >)
	char **envp;
	struct s_cmd *next; // Pointer to the next command in case of pipes
}	t_cmd;

// PARSER

// EXECUTOR
int out_rd(t_cmd *cmd);
void print_file_by_fd(int fd);

#endif
