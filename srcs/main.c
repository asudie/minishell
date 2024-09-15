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

static int		ft_minihell(t_mhell *mhell);
static t_mhell	*ft_init_minihell(t_mhell *mhell, char **envp);

int	main(int argc, char **argv, char **envp)
{
	t_mhell	mhell;

	if (argv && argc > 1)
		return (printf(ER ER_ARG), EXIT_FAILURE);
	ft_alloc_init();
	return (ft_minihell(ft_init_minihell(&mhell, envp)));
}

static int	ft_minihell(t_mhell *mhell)
{
	// Set up signal handlers
    struct sigaction sa;

    // Setup the signal handler for SIGINT (Ctrl+C)
    sa.sa_handler = sigint_handler;
    sa.sa_flags = SA_RESTART; // Automatically restart interrupted syscalls
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    signal(SIGQUIT, sigquit_handler);  // Ignore Ctrl+\/
	while (1)
	{
		// mhell->cmd_line = readline(ft_get_prompt(mhell));
		mhell->cmd_line = readline(YELLOW"minishell$ "RESET);
		if (!mhell->cmd_line)
		{
			ft_free(mhell->cmd_line);
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		if (mhell->cmd_line && *mhell->cmd_line)
			add_history(mhell->cmd_line);
		if (ft_input_parse(mhell))
		{
			if (mhell->cmd->args[0])
			{
				if (ft_strcmp(mhell->cmd->args[0], "exit") == 0)
					return (printf("exit\n"), ft_free_mhell_data(mhell), ft_destructor(), EXIT_SUCCESS);
			}
			mhell->cmd->envp = mhell->envp;
			mhell->exit_code = execute_cmd(mhell->cmd);
		}
		ft_free_mhell_data(mhell);
		ft_free(mhell->cmd_line);
	}
	ft_destructor();
	return (mhell->exit_code);
}

static t_mhell	*ft_init_minihell(t_mhell *mhell, char **envp)
{
	mhell->cmd_line = NULL;
	mhell->exit_code = EXIT_SUCCESS;
	mhell->envp = envp;
	mhell->env = NULL;
	mhell->tkn_l = 0;
	mhell->tkn = NULL;
	mhell->cmd_l = 0;
	mhell->cmd = NULL;
	ft_init_env(mhell, envp);
	return (mhell);
}
