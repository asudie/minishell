#include "../incl/minishell.h"

void	ft_parsing(t_cmd *cmd, char *input)
{
	char **tmp = ft_split(input, ' ');
	int i = 0;
	while(tmp[i])
	{
		printf("args[%d]: %s\n", i, tmp[i]);
		i++;
	}
	cmd->args = tmp;
}
