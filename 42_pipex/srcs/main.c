/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/20 16:19:11 by svalchuk		  #+#	#+#			 */
/*   Updated: 2024/06/05 21:05:59 by svalchuk		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

// #include "../incl/pipex.h"
#include "../../incl/minishell.h"

static t_pipex	ft_init_pipex(char **argv, char **envp);
static void		ft_pipex(t_pipex *pipex);
static void		ft_input_process(t_pipex *pipex, char *path, \
									int input, int *fd);
static void		ft_output_process(t_pipex *pipex, char *path, \
									int output, int *fd);

int	pipex(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		ft_error_output(NULL, "Invalid number of arguments\n", 1);
	pipex = ft_init_pipex(argv, envp);
	ft_pipex(&pipex);
	ft_free_array(pipex.cmd1);
	ft_free_array(pipex.cmd2);
	free(pipex.input_file);
	free(pipex.output_file);
	free(pipex.path);
	return (0);
}

static t_pipex	ft_init_pipex(char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;

	i = 0;
	ft_validate_file(argv);
	ft_validate_cmd(argv);
	pipex.input_file = ft_strdup(argv[1]);
	pipex.output_file = ft_strdup(argv[4]);
	pipex.cmd1 = ft_split(argv[2], ' ');
	pipex.cmd2 = ft_split(argv[3], ' ');
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	pipex.path = ft_strdup(envp[i]);
	pipex.path1 = ft_find_path(pipex.cmd1[0], pipex.path);
	pipex.path2 = ft_find_path(pipex.cmd2[0], pipex.path);
	pipex.envp = envp;
	return (pipex);
}

// static void	ft_pipex(t_pipex *pipex)
// {
// 	pid_t	pid;
// 	int		input;
// 	int		output;
// 	int		fd[2];

// 	if (pipex->cmd1[0] == NULL || pipex->cmd2[0] == NULL)
// 		ft_error_output(NULL, "Invalid command\n", 1);
// 	input = open(pipex->input_file, O_RDONLY, 0777);
// 	output = open(pipex->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	if (pipe(fd) == -1)
// 		ft_error_output(NULL, "Pipe\n", 1);
// 	pid = fork();
// 	if (pid == 0)
// 		ft_input_process(pipex, pipex->path1, input, fd);
// 	close(fd[1]); 1 - out 0 - in
// 	waitpid(pid, NULL, 0);
// 	ft_output_process(pipex, pipex->path2, output, fd);
// 	close(fd[0]);
// 	free(pipex->path1);
// 	free(pipex->path2);
// }

static void	ft_input_process(t_cmd *cmd, int input, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	dup2(input, STDIN_FILENO);
	close(input);
	if (start_exec(cmd) != 0)
		ft_error_output(NULL, "input process fails\n", 1);
}

static void	ft_output_process(t_cmd *cmd, int output, int *fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(output, STDOUT_FILENO);
		close(output);
		if (start_exec(cmd) != 0)
			ft_error_output(NULL, "output process fails\n", 1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			exit(1);
	}
}

// void execute_pipeline(char **commands, char **envp) {
//     int num_cmds = 0;
//     while (commands[num_cmds] != NULL) num_cmds++;

//     int pipefd[2 * (num_cmds - 1)];
//     pid_t pid;
//     int i, j;

//     // Create pipes
//     for (i = 0; i < (num_cmds - 1); i++) {
//         if (pipe(pipefd + i * 2) == -1) {
//             perror("pipe");
//             exit(EXIT_FAILURE);
//         }
//     }

//     // Fork processes and execute commands
//     for (i = 0; i < num_cmds; i++) {
//         pid = fork();
//         if (pid == -1) {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         } else if (pid == 0) {
//             // Child process

//             // Redirect input from previous pipe if not the first command
//             if (i > 0) {
//                 dup2(pipefd[(i - 1) * 2], STDIN_FILENO);
//             }

//             // Redirect output to next pipe if not the last command
//             if (i < num_cmds - 1) {
//                 dup2(pipefd[i * 2 + 1], STDOUT_FILENO);
//             }

//             // Close all pipe file descriptors
//             for (j = 0; j < 2 * (num_cmds - 1); j++) {
//                 close(pipefd[j]);
//             }

//             // Split command into program and arguments
//             char *args[256];
//             char *cmd = strdup(commands[i]);
//             char *token = strtok(cmd, " ");
//             int k = 0;
//             while (token != NULL) {
//                 args[k++] = token;
//                 token = strtok(NULL, " ");
//             }
//             args[k] = NULL;

//             // Execute the command
//             execvp(args[0], args);
//             perror("execvp");
//             exit(EXIT_FAILURE);
//         }
//     }

//     // Parent process
//     // Close all pipe file descriptors
//     for (i = 0; i < 2 * (num_cmds - 1); i++) {
//         close(pipefd[i]);
//     }

//     // Wait for all child processes to finish
//     for (i = 0; i < num_cmds; i++) {
//         wait(NULL);
//     }
// }