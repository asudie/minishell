/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:13:50 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/19 14:16:18 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	*ft_get_prompt(t_mhell *mhell);
static char	*ft_prompt_exit_code(t_mhell *mhell, char *prompt);

char	*ft_input_prompt(t_mhell *mhell)
{
	char	*input;

	input = readline(ft_get_prompt(mhell));
	if (!input)
	{
		ft_free(input);
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (input && *input)
		add_history(input);
	return (input);
}

static char	*ft_get_prompt(t_mhell *mhell)
{
	static char	*prompt;
	t_env		*user;
	char		*home;
	char		*cwd;
	char		*tmp;

	user = ft_find_env(mhell->env, "HOME");
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		printf("\nyou can use only 'cd ..' or 'exit'\n\n");
		return (prompt);
	}
	if (user == NULL)
		home = "/";
	else
		home = user->val;
	tmp = ft_strjoin(ft_substr_rem(cwd, home), "$ ");
	ft_free(cwd);
	prompt = ft_prompt_exit_code(mhell, ft_strjoin("~", tmp));
	ft_free(tmp);
	return (prompt);
}

static char	*ft_prompt_exit_code(t_mhell *mhell, char *input)
{
	char	*prompt;
	char	*tmp;
	char	*code;

	prompt = ft_strjoin(YELLOW"Minishell:"WHITE, input);
	if (mhell->exit_code == 0)
		tmp = ft_strjoin(WHITE"["BLUE"0"WHITE"]", prompt);
	else
	{
		tmp = ft_strjoin(WHITE"["RED, ft_itoa(mhell->exit_code));
		code = ft_strjoin(tmp, WHITE"]");
		ft_free(tmp);
		tmp = ft_strjoin(code, prompt);
		ft_free(code);
	}
	prompt = ft_strjoin(tmp, RESET);
	ft_free(tmp);
	return (prompt);
}
