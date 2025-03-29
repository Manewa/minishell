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

static	int	ft_check_option_echo(char **cmd, int *i)
{
	int	j;
	int	nl;

	nl = 1;
	while (cmd[*i])
	{
		j = 0;
		if (cmd[*i][j] == '-')
		{
			j++;
			while (cmd[*i][j] == 'n')
				j++;
			if (!cmd[*i][j])
				nl = 0;
			else
				break ;
		}
		else
			break ;
		*i += 1;
	}
	return (nl);
}

int	ft_echo(t_exec *exec)
{
	int	i;
	int	nl;

	i = 1;
	nl = ft_check_option_echo(exec->cmd_array, &i);
	if (exec->cmd_array[i])
	{
		ft_putstr_fd(exec->cmd_array[i], exec->files->outfile->fd);
		i++;
	}
	while (exec->cmd_array[i])
	{
		ft_putstr_fd(" ", exec->files->outfile->fd);
		ft_putstr_fd(exec->cmd_array[i], exec->files->outfile->fd);
		i++;
	}
	if (nl)
		ft_putstr_fd("\n", exec->files->outfile->fd);
	return (0);
}
