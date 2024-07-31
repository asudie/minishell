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
// 	close(fd[1]);
// 	waitpid(pid, NULL, 0);
// 	ft_output_process(pipex, pipex->path2, output, fd);
// 	close(fd[0]);
// 	free(pipex->path1);
// 	free(pipex->path2);
// }

static void	ft_input_process(t_cmd *cmd, int input, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO); // WHAT IS THIS!!!!!!!
	close(fd[1]);
	dup2(input, STDIN_FILENO); // WHAT IS THIS!!!!!!!
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
		dup2(fd[0], STDIN_FILENO); // WHAT IS THIS!!!!!!!
		close(fd[0]);
		dup2(output, STDOUT_FILENO); // WHAT IS THIS!!!!!!!
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

// void execute_pipeline(char ***commands) {
//     int num_cmds = count_commands(commands);
//     int pipefd[2];
//     pid_t pid;
//     int fd_in = 0; // First process should read from stdin

//     for (int i = 0; i < num_cmds; i++) {
//         pipe(pipefd);

//         if ((pid = fork()) == -1) {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         } else if (pid == 0) {
//             dup2(fd_in, STDIN_FILENO); // Redirect stdin to fd_in
//             if (i < num_cmds - 1)
//                 dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe write end

//             close(pipefd[0]);
//             execvp(commands[i][0], commands[i]);
//             perror("execvp");
//             exit(EXIT_FAILURE);
//         } else {
//             wait(NULL); // Wait for child to finish
//             close(pipefd[1]);
//             fd_in = pipefd[0]; // Save the read end of the pipe for the next command
//         }
//     }
// }
