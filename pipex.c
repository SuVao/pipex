/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:58:30 by pesilva-          #+#    #+#             */
/*   Updated: 2024/08/22 16:00:42 by pesilva-         ###   ########.fr       */
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
void	child_processe(char **av, char *envp, int *fd)
{
	int filein;
	
	if (filein = open(av[1], O_RDONLY, 0777) == -1)
	{
		perror("filein fail!");
		return (4);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	execut(av[2], envp);
}

void	nd_child_process(char **av, char *envp, int *fd)
{
	int	fileout;

	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
	{
		perror("fileout fail!");
		return (5);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDIN_FILENO);
	close(fd[1]);
	execut(av[3], envp);
}

int main(int ac, char **av, char **envp)
{
	int	pid;
	int	pid2;
	int	fd[2];
	
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
		child_processe(av[2], *envp, fd);
	if (pid != 0)
	{
		pid2 = fork();
		if (pid2 == -1)
		{
			perror("fork 2 failed!");
			return (6);
		}
		if (pid2 == 0)
			nd_child_process(av[3], *envp, fd);
		else
			wait(NULL);
	}
}