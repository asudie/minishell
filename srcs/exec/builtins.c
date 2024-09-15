/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c		                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:22:44 by ******           #+#    #+#              */
/*   Updated: 2024/07/22 00:43:38 by ******           ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	handle_null_arg(t_cmd *cmd, char **path);
static int	handle_dash_arg(t_cmd *cmd, char **path);
static int	handle_tilde_arg(t_cmd *cmd, char **path);
static int	change_directory_and_update_env(t_cmd *cmd, char *path);

int	builtin_cd(t_cmd *cmd)
{
	char	*path;
	int		result;

	path = NULL;
	result = 0;
	if (cmd->args[1] == NULL)
		result = handle_null_arg(cmd, &path);
	else if (ft_strcmp(cmd->args[1], "-") == 0)
		result = handle_dash_arg(cmd, &path);
	else if (cmd->args[1][0] == '~')
		result = handle_tilde_arg(cmd, &path);
	else
		path = cmd->args[1];
	if (result == 0)
		result = change_directory_and_update_env(cmd, path);
	if (cmd->args[1] && cmd->args[1][0] == '~' && path != NULL)
		free(path);
	return (result);
}

static int	handle_null_arg(t_cmd *cmd, char **path)
{
	char	*home_dir;

	home_dir = get_env_var(cmd->envp, "HOME");
	if (home_dir == NULL)
	{
		ft_printf("cd: HOME not set\n");
		return (1);
	}
	*path = home_dir;
	return (0);
}

static int	handle_dash_arg(t_cmd *cmd, char **path)
{
	char	*oldpwd;

	oldpwd = get_env_var(cmd->envp, "OLDPWD");
	if (oldpwd == NULL)
	{
		ft_printf("cd: OLDPWD not set\n");
		return (1);
	}
	*path = oldpwd;
	return (0);
}

static int	handle_tilde_arg(t_cmd *cmd, char **path)
{
	char	*home_dir;

	home_dir = get_env_var(cmd->envp, "HOME");
	if (home_dir == NULL)
	{
		ft_printf("cd: HOME not set\n");
		return (1);
	}
	*path = malloc(ft_strlen(home_dir) + ft_strlen(cmd->args[1]));
	if (*path == NULL)
	{
		perror("malloc");
		return (1);
	}
	ft_strcpy(*path, home_dir);
	ft_strlcat(*path, cmd->args[1] + 1, ft_strlen(home_dir) \
		+ ft_strlen(cmd->args[1]));
	return (0);
}

static int	change_directory_and_update_env(t_cmd *cmd, char *path)
{
	char	cwd[1024];
	char	*oldpwd;

	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	oldpwd = get_env_var(cmd->envp, "PWD");
	if (oldpwd != NULL)
		set_env_var(cmd->envp, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		set_env_var(cmd->envp, "PWD", cwd);
	else
	{
		perror("getcwd");
		return (1);
	}
	return (0);
}
