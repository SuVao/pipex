/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:58:30 by pesilva-          #+#    #+#             */
/*   Updated: 2024/08/23 17:22:35 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* int main(int ac, char **av, char **envp)
{
	int	fd[2];
	int	pid;

	if (ac == 5)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("falha no fork");
			return (1);
		}
		if (pid == 0)
		{
			int err;
			err = execve(av[1], &av[2], envp);
			if (err == -1)
			{
				perror("erro ao executar");
				return (2);
			}
		}
		else
		{
			wait(NULL);
			printf("pai\n");
		}
	}
	else
		perror("numero de argumentos invalido");
} */

/* int main(int ac, char **av)
{
	int pid;
	int fd[2];
	int x, y;
	
	if (ac != 3)
	{
		perror("nbr of arguments invalid");
		return (1);
	}
	if (pipe(fd) == -1)
	{
		perror("pipe failed");
		return (2);
	}
	x = atoi(av[1]);
	y = atoi(av[2]);
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (3);
	}
	if (pid == 0) //child processe
	{
		close(fd[0]);
		read(fd[0], &x, sizeof(x));
		read(fd[0], &y, sizeof(y));
		x *= y;
		printf("x = %d\n", x);
		close(fd[1]);
	}
	else // parent processe
	{
		close(fd[0]);
		write(fd[1], &x, sizeof(x));
		write(fd[1], &y, sizeof(y));
		printf("y = %d x = %d\n", y, x);
		close(fd[1]);
	}
	int pid2;

	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork failed");
		return (4);
	}

	if (pid2 == 0)
	{
		close(fd[0]);
		x /= y;
		printf("x = %d\n", x);
		close(fd[1]);
	}
	
	return (0);
} */

//opening and creating the infile and redir the pipe 
/* void	child_processe(char **av, char *envp, int *fd)
{
	int filein;
	
	filein = open(av[1], O_RDONLY | O_CREAT | O_TRUNC, 0777);
	if (filein == -1)
	{
		perror("filein fail!");
		return ;
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	(void)envp;
	execut(av[2], envp);
}

void	nd_child_process(char **av, char *envp, int *fd)
{
	int	fileout;

	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
	{
		perror("fileout fail!");
		return ;
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDIN_FILENO);
	close(fd[1]);
	(void)envp;

	execut(av[3], envp);
}

int main(int ac, char **av, char **envp)
{
	int	pid;
	int	pid2;
	int	fd[2];
	
	(void)envp;
	if (ac != 5)
	{
		perror("Invalid number of arguments!");
		return (1);
	}
	if (pipe(fd) == -1)
	{
		perror("pipe error!");
		return (2);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork fail!");
		return (3);
	}
	if (pid == 0)
		child_processe(&av[2], *envp, fd);
	if (pid != 0)
	{
		pid2 = fork();
		if (pid2 == -1)
		{
			perror("fork 2 failed!");
			return (4);
		}
		if (pid2 == 0)
			nd_child_process(&av[3], *envp, fd);
		else
			wait(NULL);
	}
} */

static void	st_child(int *fd, char **av, char **envp)
{
	int	filein;

	if (!fd || !av || !envp)
		return ;
	close(fd[0]);
	filein = open(av[1], O_RDONLY);
	if (filein < 0)
		error_m("error in filein", &fd[1], NULL);
	if (dup2(filein, STDIN_FILENO) == -1)
		error_m("Error in dup2 filein", &filein, &fd[1]);
	close(filein);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error_m("Error in dup2 fd[1]", NULL, &fd[1]);
	close(fd[1]);
	//exec_st_cmd(av[2], envp);
	printf("1 filho");
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
	if (dup2(fileout, STDIN_FILENO) == -1)
		error_m("error in dup2 fileout", &fileout, &fd[0]);
	if (dup2(fd[0], STDOUT_FILENO) == -1)
		error_m("error in dup2 fd[0]", &fd[0], NULL);
	close(fd[0]);
	printf("2 filho");
}

static void	close_fd(int count, int *fd)
{
	if (count == 0)
		close(fd[1]);
	else if (count == 1)
		close(fd[0]);
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
			else
				nd_child(fd, av, envp);
		}
		else
			close_fd(count, fd);
		count++;
	}
}

int	execucao(char **av, int *fd, char **envp, int *status)
{
	int	pid;

	pid = 1;
	if (!av || !fd || !envp)
	{
		error_m("Error in execucao function!", NULL, NULL);
		return (1);
	}
	fork_exec(av, fd, envp, pid);
	waitpid(pid, status, 0);
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