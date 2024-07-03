#include "../incl/minishell.h"

void	ft_parsing(t_cmd *cmd, char *input)
{
	cmd->args = ft_split(input, ' ');
	int i = 0;
	while(cmd->args[i])
	{
		printf("args[%d]: %s\n", i, cmd->args[i]);
		i++;
	}
}
