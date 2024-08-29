/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:54:46 by pesilva-          #+#    #+#             */
/*   Updated: 2024/08/29 15:59:25 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//mensage of error and close the pipes
void	error_m(char *mensage, int *fd1, int *fd2)
{
	if (!mensage)
		return ;
	if (fd1)
		close(*fd1);
	if (fd2)
		close(*fd2);
	perror(mensage);
	exit(EXIT_FAILURE);
}

//checking if the path exists
int	path_exits(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != 0)
			return (1);
		i++;
	}
	return (0);
}

//fuction to find the path
char	*path_find(char **envp, char *cmd)
{
	int		i;
	char	**possible_ways;
	char	*path;

	if (!envp || !cmd)
		return (NULL);
	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	possible_ways = ft_split(envp[i] + 19, ':');
	i = 0;
	while (possible_ways[i])
	{
		path = ft_append_str(possible_ways[i], "/", cmd);
		if (access(path, F_OK) == 0)
			break ;
		else
		{
			free(path);
			path = NULL;
			i++;
		}
	}
	ft_free_matrix(possible_ways);
	return (path);
}

//function to free everything
void	ft_free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

// fuction of checking if cmd exists and spliting comands 
void	execute(char *av, char **envp)
{
	char	**cmd;
	char	*path;

	if (!av || !envp)
		return ;
	cmd = NULL;
	path = NULL;
	cmd = ft_split(av, ' ');
	path = path_find(envp, cmd[0]);
	if (!path)
	{
		free_all(cmd, path);
		write(2, "Command not found\n", 19);
		exit(127);
	}
	if (execve(path, cmd, envp) == -1)
	{
		free_all(cmd, path);
		error_m("Error in execve", NULL, NULL);
	}
}
