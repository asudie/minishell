#include "../../incl/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd = malloc(sizeof(t_cmd));

	// Initialize environment variables
	// init_environment(envp);

    // Set up signal handlers
    // signal(SIGINT, sigint_handler);  // Handle Ctrl+C
    // signal(SIGQUIT, sigquit_handler);  // Ignore Ctrl+\/

	// while (1)
	// {

    // Read input (you would implement your actual input handling here)
        // char buffer[1024];
        // if (fgets(buffer, sizeof(buffer), stdin) == NULL) {  CTRL-D
        //     if (feof(stdin)) {
        //         break;
        //     }
        // }
		
		// cmd = malloc(sizeof(t_cmd));
        // EXAMPLE: ls -l > output.txt
		// cmd.cmd = "ls";
		// cmd.args = (char *[]){"ls", "-l", NULL};
		// cmd->in_rd = NULL;
		// cmd.out_rd = "output.txt";
		// cmd.append = 0;
		// cmd.next = NULL;

		// cmd.cmd = "echo";
		// cmd.args = (char *[]){"echo", "Hello!", NULL};
		// cmd.cmd = "cd";
		// cmd.args = (char *[]){"cd", "/bin"};
		
        //PWD
        printf("CMD: cat Makefile\n");
		cmd->args = (char *[]){"cd", "/", NULL};
        printf("OUTPUT:\n");

        // ENV
		// cmd.args = (char *[]){"env", NULL};
        
		// cmd.in_rd = "/home/asmolnya/Projects/minishell/srcs/exec/input.txt";
		cmd->out_rd = NULL;
		cmd->append = 0;
		cmd->next = NULL;
		cmd->envp = envp;
        cmd->in_rd = NULL;

        // cmd->next->args = (char *[]){"wc", "-l", NULL};
        // cmd->next->out_rd = NULL;
		// cmd->next->append = 0;
		// cmd->next->next = NULL;
		// cmd->next->envp = envp;
        // cmd->next->in_rd = NULL;

		// display_prompt(&cmd); 
		// Execute cmd
		// execute_cmd(&cmd);
        // cmd.cmd = "unset";
		// cmd.args = (char *[]){"unset", "USER", NULL};
        // cmd.cmd = "export";
        // cmd.args = (char *[]){"export", "MYVAR=3", NULL};
        // if(execute_cmd(&cmd))
        //    return 0;
        // cmd.cmd = "exit";
        // cmd.args = (char *[]){"exit", NULL};
        // if(execute_cmd(&cmd))
        //     return 0;
		// cmd.args = (char *[]){"copy", "/home/asmolnya/Projects/minishell/srcs/exec/input.txt", NULL};  // if doesn't work add the PATH
        if(execute_cmd(cmd))
        {
            
            return 0; 
        }
            // printf("FINALE %d\n", exit_status); // WHY HER IT'S 0??????????????????????????????????????????????????????
        // cmd->next->args = (char *[]){"echo", "$?" NULL};
        // cmd.append = 1;
        // if(execute_cmd(&cmd))
        //     return 0;
		// display_prompt(&cmd);
		// ft_free allocated memory
		// free_input(input);
		// free_cmd(cmd);
	// }
	return (0);
}