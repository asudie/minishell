#include "../incl/minishell.h"

static void	ft_init_minihell(t_mhell *mhell, char **envp);
static void	ft_minihell(t_mhell *mhell);
static int	ft_input_check(char *input);

int	main(int argc, char **argv, char **envp)
{
	t_mhell	mhell;

	(void)argv;
	ft_alloc_init();
	if (argc != 1)
	{
		printf(ERR ERR_ARG);
		return (1);
	}
	else
	{
		ft_init_minihell(&mhell, envp);
		ft_minihell(&mhell);
	}
	ft_destructor();
	return (0);
}

static void	ft_init_minihell(t_mhell *mhell, char **envp)
{
	mhell->env = NULL;
	mhell->cmd = NULL;
	ft_init_env(mhell, envp);
}

static void	ft_minihell(t_mhell *mhell)
{
	char	*input;
	char	*path;

	while (1)
	{
		input = readline(YELLOW"Mhell$ "RESET);
		if (ft_input_check(input))
			continue ;
		add_history(input);
		if (ft_input_parse(mhell, input))
		{
			//executor(mhell);
		}
		ft_free(input);
	}
	rl_clear_history();
	ft_free(path);
}

static int	ft_input_check(char *input)
{
	if (!input)
	{
		ft_free(input);
		printf(PURPLE"exit\n"RESET);
		exit(EXIT_SUCCESS);
	}
	else if (!*input)
	{
		ft_free(input);
		return (1);
	}
	return (0);
}
