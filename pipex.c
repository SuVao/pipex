/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:58:30 by pesilva-          #+#    #+#             */
/*   Updated: 2024/08/26 19:23:52 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	st_child(int *fd, char **av, char **envp)
{
	int	filein;

	if (!fd || !av || !envp)
		return ;
	close(fd[0]);
	filein = open(av[1], O_RDONLY);
	if (filein < 0)
		error_m("Error in filein", &fd[1], NULL);
	if (dup2(filein, STDIN_FILENO) == -1)
		error_m("Error in dup2 filein", &filein, &fd[1]);
	close(filein);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error_m("Error in dup2 fd[1]", &fd[1], NULL);
	close(fd[1]);
	execute(av[2], envp);
}

static void nd_child(int *fd, char **av, char **envp)
{
	int	fileout;
	int	existe;
	
	if (!fd || !av || !envp)
		return ;
	existe = 0;
	if (access(av[4], F_OK) == 0)
		existe = 1;
	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		error_m("fileout error", &fd[0], NULL);
	if (dup2(fileout, STDOUT_FILENO) == -1)
		error_m("Error in dup2 fileout", &fileout, &fd[0]);
	if (dup2(fd[0], STDOUT_FILENO) == -1)
		error_m("Error in dup2 fd[0]", &fd[0], NULL);
	close(fd[0]);
	execute(av[3], envp);
}

static void	close_fd(int count, int *fd)
{
	if (!fd)
		error_m("Error in close_fd function!", NULL, NULL);
	if (count == 0)
		close(fd[1]);
	else if (count == 1)
		close(fd[0]);
	if(count == 1)
	{
		close(fd[0]);
		close(fd[1]);
	}
}

static void	fork_exec(char **av, int *fd, char **envp, int pid)
{
	int	count;
	
	count = 0;
	while (count <= 1)
	{
		pid = fork();
		if (pid == -1)
		{
			error_m("fork error!", &fd[0], &fd[1]);
			return ;
		}
		else if (pid == 0)
		{
			if (count == 0)
				st_child(fd, av, envp);
			else if (count == 1)
				nd_child(fd, av, envp);
		}
		else
			close_fd(count, fd);
		count++;
	}
}

static int	execucao(char **av, int *fd, char **envp, int *status)
{
	int	pid;

	if (!av || !fd || !envp)
		error_m("Error in execucao function!", NULL, NULL);
	pid = 0;
	fork_exec(av, fd, envp, pid);
	waitpid(pid, status, 0);
	waitpid(-1, status, 0);

	/* while (pid[--i] >= 0)
	{
		waitpid(pid[i], status, 0);
		i++;
	} */
	return (0);
}

int main(int ac, char **av, char **envp)
{
	int	fd[2];
	int	status;
	
	if(ac != 5)
		error_m("Number of arguments invalid!", NULL, NULL);
	if (pipe(fd) == -1)
		error_m("pipe error!", NULL, NULL);
	if (!execucao(av, fd, envp, &status))
		error_m("exec fail!", NULL, NULL);
	status = WEXITSTATUS(status);
	return (status);
}