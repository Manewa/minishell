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

int	ft_echo(t_exec *exec)
{
	int	i;
	int	nl;

	i = 1;
	nl = 0;
	if (!exec->cmd_array[i] || ft_strcmp("-n", exec->cmd_array[1]))
		nl = 1;
	else
		i++;
	if (exec->cmd_array[i])
	{
		ft_putstr_fd(exec->cmd_array[i], exec->files->outfile->fd);
		i++;
	}
	while (exec->cmd_array[i])
	{
		ft_putstr_fd(" ",  exec->files->outfile->fd);
		ft_putstr_fd(exec->cmd_array[i], exec->files->outfile->fd);
		i++;
	}
	if (nl)
		ft_putstr_fd("\n", exec->files->outfile->fd);
	return (0);
}