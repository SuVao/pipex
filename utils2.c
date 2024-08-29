/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:02:58 by pesilva-          #+#    #+#             */
/*   Updated: 2024/08/29 16:06:17 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//funtion that closes the file descripter
void	close_fd(int count, int *fd)
{
	if (!fd)
		error_m("Error in close_fd function!", NULL, NULL);
	if (count == 0)
		close(fd[1]);
	else if (count == 1)
		close(fd[0]);
}

//function to free all
void	free_all(char **matrix, char *str)
{
	if (matrix)
		ft_free_matrix(matrix);
	if (str)
		free(str);
}
