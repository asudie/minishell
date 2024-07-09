#include "../incl/minishell.h"

int	main()
{
    t_cmd *cmd;
	char *input;

    ft_alloc_init();
    // Display a prompt and read input
    cmd = ft_malloc(sizeof(t_cmd));
    while ((input = readline(COLOR_YELLOW"minishell$ "COLOR_RESET)) != NULL){
        // If input is not empty, add it to the history
        if (*input) {
            add_history(input);
        }
        ft_parsing(cmd, input);

        // Process the input
        printf("You entered: %s\n", input);
    }

    // Clear the history list
    rl_clear_history();
    ft_destructor();
	return (0);
}
