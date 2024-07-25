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

#include "../incl/pipex.h"

static t_pipex	ft_init_pipex(char **argv, char **envp);
static void		ft_pipex(t_pipex *pipex);
static void		ft_input_process(t_pipex *pipex, char *path, \
									int input, int *fd);
static void		ft_output_process(t_pipex *pipex, char *path, \
									int output, int *fd);

int	main(int argc, char **argv, char **envp)
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

static void	ft_pipex(t_pipex *pipex)
{
	pid_t	pid;
	int		input;
	int		output;
	int		fd[2];

	if (pipex->cmd1[0] == NULL || pipex->cmd2[0] == NULL)
		ft_error_output(NULL, "Invalid command\n", 1);
	input = open(pipex->input_file, O_RDONLY, 0777);
	output = open(pipex->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipe(fd) == -1)
		ft_error_output(NULL, "Pipe\n", 1);
	pid = fork();
	if (pid == 0)
		ft_input_process(pipex, pipex->path1, input, fd);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	ft_output_process(pipex, pipex->path2, output, fd);
	close(fd[0]);
	free(pipex->path1);
	free(pipex->path2);
}

static void	ft_input_process(t_pipex *pipex, char *path, int input, int *fd)
{
	if (input == -1)
		ft_error_output(pipex->input_file, "No such file or directory\n", 1);
	if (path == NULL)
		ft_error_output(pipex->cmd1[0], "command not found\n", 127);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	dup2(input, STDIN_FILENO);
	close(input);
	if (execve(path, pipex->cmd1, pipex->envp) == -1)
		ft_error_output(NULL, "input process fails\n", 1);
}

static void	ft_output_process(t_pipex *pipex, char *path, int output, int *fd)
{
	pid_t	pid;
	int		status;

	if (output == -1)
		ft_error_output(pipex->output_file, "No such file or directory\n", 1);
	if (path == NULL)
		ft_error_output(pipex->cmd2[0], "command not found\n", 127);
	pid = fork();
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(output, STDOUT_FILENO);
		close(output);
		if (execve(path, pipex->cmd2, pipex->envp) == -1)
			ft_error_output(NULL, "output process fails\n", 1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			exit(1);
	}
}
