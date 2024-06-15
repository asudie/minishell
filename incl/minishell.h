/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:06:47 by svalchuk          #+#    #+#             */
/*   Updated: 2024/06/15 20:31:16 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_command {
    char *command;           // The command name, e.g., "ls"
    char **args;             // An array of arguments, e.g., ["ls", "-l", NULL]
    char *input_redirection; // Input redirection file, e.g., "input.txt"
    char *output_redirection; // Output redirection file, e.g., "output.txt"
    int append;              // Flag for append mode (1 for >>, 0 for >)
    struct s_command *next;  // Pointer to the next command in case of pipes
} t_command;


#endif