#include "../../incl/minishell.h"

int resolve_full_path(t_cmd *cmd, char **full_path) {
    char	*tmp;
    char    *path = NULL;
    
    if (access(cmd->args[0], X_OK) == 0)
    {
        *full_path = cmd->args[0];
        return 0;
    }
    path = get_env_var(cmd->envp, "PATH"); 

    if (!path) {
        return 1;
    }
    char	**paths = ft_split(path + 5, ':');
    int		i = 0;
    
    while (paths[i] != NULL)
	{
        
		tmp = ft_strjoin(paths[i], "/");
		*full_path = ft_strjoin(tmp, cmd->args[0]);
		free(tmp);
		if (access(*full_path, X_OK) == 0) {
           
            ft_free_array(paths);
            return 0;
        }
		free(*full_path);
		i++;
	}
	ft_free_array(paths);
	return (1);
}
