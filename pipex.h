/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:38:42 by pesilva-          #+#    #+#             */
/*   Updated: 2024/08/28 18:11:43 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include "Libft/libft.h"

void	error_m(char *mensage, int *fd1, int *fd2);
char	*path_find(char **envp, char *cmd);
int		path_exits(char **envp);
void	ft_free_matrix(char **matrix);
void	execute(char *av, char **envp);
void	free_all(char **matrix, char *str);
void	close_fd(int count, int *fd);

#endif
