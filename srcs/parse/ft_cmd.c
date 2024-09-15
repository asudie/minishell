/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:11:40 by svalchuk          #+#    #+#             */
/*   Updated: 2024/09/14 18:11:26 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

// void	ft_print_tkn(t_mhell *mhell)
// {
// 	int	i;

// 	i = 0;
// 	while (i < mhell->tkn_l)
// 	{
// 	printf("Token: %s\tType: %d\n", mhell->tkn[i].token, mhell->tkn[i].type);
// 		i++;
// 	}
// }

// void	ft_print_cmd(t_cmd *cmd)
// {
// 	t_cmd *tmp = cmd;
// 	while (tmp)
// 	{
// 		printf("\n");
// 		for (int i = 0; tmp->args[i]; i++)
// 				printf("args[%i]: %s\n", i, tmp->args[i]);
// 		printf("rdin: %s\n", tmp->in_rd);
// 		printf("rdout: %s\n", tmp->out_rd);
// 		printf("append: %i\n", tmp->append);
// 		printf("heredoc: %i\n", tmp->heredoc);
// 		tmp = tmp->next;
// 	}
// }

t_cmd *ft_allocate_cmd(t_cmd_alloc *allocs, char **args);
void	ft_fill_cmd(t_mhell *mhell, int *i, t_cmd *cmd);

void	ft_create_cmd(t_mhell *mhell)
{
	int	i;
	int	len;
	t_cmd	*cmd = NULL;

	i = 0;
	len = -1;
	while (i < mhell->tkn_l)
	{
		if (mhell->tkn[i].type == _pipe)
			mhell->cmd_l++;
		i++;
	}
	i = 0;
	while (++len <= mhell->cmd_l)
	{
		ft_fill_cmd(mhell, &i, cmd);
		i++;
	}
	// ft_print_cmd(mhell->cmd);
}

void	ft_fill_cmd(t_mhell *mhell, int *i, t_cmd *cmd)
{
	t_cmd_alloc	*allocs;
	char		**args;
	
	int	j = -1;
	args = ft_calloc(mhell->tkn_l, sizeof(char *));
	allocs = ft_calloc(1, sizeof(t_cmd_alloc));
	while (*i < mhell->tkn_l && mhell->tkn[*i].type != _pipe)
	{
		if (mhell->tkn[*i].type == _rdin || mhell->tkn[*i].type == _hrdc)
		{
			if (mhell->tkn[*i].type == _hrdc)
				allocs->heredoc = 1;
			(*i)++;
			allocs->in_rd = ft_strdup(mhell->tkn[*i].token);
			// ft_handle_heredocs(mhell);
		}
		else if (mhell->tkn[*i].type == _rdout || mhell->tkn[*i].type == _append)
		{
			if (mhell->tkn[*i].type == _append)
				allocs->append = 1;
			(*i)++;
			allocs->out_rd = ft_strdup(mhell->tkn[*i].token);
		}
		else
		{
			allocs->num_args++;
			args[++j] = ft_strdup(mhell->tkn[*i].token);
		}
		(*i)++;
	}
	cmd = ft_allocate_cmd(allocs, args);
	ft_cmdadd_back(&mhell->cmd, cmd);
}

t_cmd *ft_allocate_cmd(t_cmd_alloc *allocs, char **args)
{
    // Step 1: Allocate memory for the t_cmd structure
    t_cmd *cmd = (t_cmd *)ft_malloc(sizeof(t_cmd));
    if (!cmd) {
        return NULL; // Allocation failed
    }

    // Step 2: Allocate memory for the args array
    cmd->args = (char **)ft_malloc((allocs->num_args + 1) * sizeof(char *)); // +1 for NULL terminator
    if (!cmd->args) {
        ft_free(cmd);
        return NULL; // Allocation failed
    }

    // Step 3: Allocate memory for each string in the args array
    for (int i = 0; i < allocs->num_args; i++) {
        cmd->args[i] = (char *)ft_malloc(256 * sizeof(char)); // Assuming max length of 256 for each argument
        if (!cmd->args[i]) {
            // Free previously allocated memory in case of failure
            for (int j = 0; j < i; j++) {
                ft_free(cmd->args[j]);
            }
            ft_free(cmd->args);
            ft_free(cmd);
            return NULL; // Allocation failed
        }
    }
	int j = -1;
	while (args[++j])
		cmd->args[j] = args[j];
	cmd->args[allocs->num_args] = NULL; // NULL terminator

    // Step 4: Allocate memory for in_rd and out_rd if they are not NULL
    if (allocs->in_rd) {
        cmd->in_rd = ft_strdup(allocs->in_rd);
        if (!cmd->in_rd) {
            // Free previously allocated memory in case of failure
            for (int i = 0; i < allocs->num_args; i++) {
                ft_free(cmd->args[i]);
            }
            ft_free(cmd->args);
            ft_free(cmd);
            return NULL; // Allocation failed
        }
    } else {
        cmd->in_rd = NULL;
    }

    if (allocs->out_rd) {
        cmd->out_rd = ft_strdup(allocs->out_rd);
        if (!cmd->out_rd) {
            // Free previously allocated memory in case of failure
           	ft_free(cmd->in_rd);
            for (int i = 0; i < allocs->num_args; i++) {
                ft_free(cmd->args[i]);
            }
            ft_free(cmd->args);
            ft_free(cmd);
            return NULL; // Allocation failed
        }
    } else {
        cmd->out_rd = NULL;
    }

    // Set other fields
    cmd->append = allocs->append;
    cmd->heredoc = allocs->heredoc;
    cmd->next = NULL;

    return cmd;
}

/*
< in ls -l | wc -c > out | cat << g | echo "Hello World!" >> out | echo "No $PWD" | echo 'Yes $SHLVL'
*/