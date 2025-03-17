/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <aibonade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:33:46 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/17 10:33:49 by aibonade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(t_exec *exec, int std_fd)
{
	int	i;
	int	nl;

	i = 1;
	nl = 0;
	if (!exec->cmd_array[i] || ft_strcmp("-n", exec->cmd_array[1]))//, 3))
		nl = 1;
	else
		i++;
	if (exec->cmd_array[i])
	{
		ft_putstr_fd(exec->cmd_array[i], exec->files->outfile->fd);
		// printf("%s", exec->cmd_array[i]);
		i++;
	}
	while (exec->cmd_array[i])
	{
		// printf(" %s",exec->cmd_array[i]);
		ft_putstr_fd(" ",  exec->files->outfile->fd);
		ft_putstr_fd(exec->cmd_array[i], exec->files->outfile->fd);
		i++;
	}
	if (nl)
		ft_putstr_fd("\n", exec->files->outfile->fd);
		// printf("\n");
	// // else if (exec->files->outfile->fd && std_fd < 2)
	// // 	close(exec->files->outfile->fd);
(void) std_fd;
	return (0);
}