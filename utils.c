/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:54:46 by pesilva-          #+#    #+#             */
/*   Updated: 2024/08/23 17:08:22 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void error_m(char *mensage, int *fd1, int *fd2)
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