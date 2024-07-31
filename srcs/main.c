/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:22:44 by ******           #+#    #+#              */
/*   Updated: 2024/07/22 00:43:38 by ******           ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "../incl/minishell.h"

static t_mhell	*ft_init_minihell(t_mhell *mhell, char **envp);
static int		ft_minihell(t_mhell *mhell);

int	main(int argc, char **argv, char **envp)
{
	t_mhell	mhell;

	if (argv && argc > 1)
	{
		printf(ER ER_ARG);
		return (EXIT_FAILURE);
	}
	ft_alloc_init();
	return (ft_minihell(ft_init_minihell(&mhell, envp)));
}

static t_mhell	*ft_init_minihell(t_mhell *mhell, char **envp)
{
	mhell->env = NULL;
	mhell->cmd = NULL;
	mhell->cmd->envp = envp;
	mhell->exit_code = EXIT_SUCCESS;
	ft_init_env(mhell, envp);
	return (mhell);
}

static int	ft_minihell(t_mhell *mhell)
{
	char	*input;

	while (1)
	{
		input = ft_input_prompt(mhell);
		printf("%s\n", input);
		if (ft_atoi(input) >= 0)
			mhell->exit_code = ft_atoi(input);
		if (ft_input_error(mhell, input))
			continue ;
		// if (ft_input_parse(mhell, input))
		// {
			// for (t_cmd *cmd = mhell->cmd; cmd != NULL; cmd = cmd->next) {
			// 	printf("Command: ");
			// 	for (int i = 0; cmd->args[i]; i++){
			// 		printf("%s ", cmd->args[i]);
			// 	}
			// 	printf("\n");
			// }
			//exitcode = executor(mhell->cmd);
		// }
		ft_free(input);
	}
	rl_clear_history();
	ft_destructor();
	return (mhell->exit_code);
}
