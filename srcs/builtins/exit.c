/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <aibonade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:48:13 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/16 13:48:16 by aibonade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_nb_args_exit(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->cmd_array[i])
		i++;
	return (i);
}

static int	ft_check_arg_exit(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->cmd_array[1][i] == ' ')
		i++;
	if (exec->cmd_array[1][i] == '+' || exec->cmd_array[1][i] == '-')
		i++;
	if (!ft_isdigit(exec->cmd_array[1][i]))
	{
		ft_putstr_fd("minipouet: exit: ", 2);
		ft_putstr_fd(exec->cmd_array[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (1);
	}
	while (exec->cmd_array[1][i] && ft_isdigit(exec->cmd_array[1][i]))
		i++;
	if (exec->cmd_array[1][i])
	{
		ft_putstr_fd("minipouet: exit: ", 2);
		ft_putstr_fd(exec->cmd_array[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (1);
	}
	return (0);
}

int	ft_exit(t_exec *exec, int fd_pipe[2])
{
	int	ret;
	int	nb_arg;

	if (exec == exec->head && exec->next == NULL)
		ft_putstr_fd("exit\n", exec->files->outfile->fd);
	nb_arg = ft_nb_args_exit(exec);
	ret = 0;
	if (nb_arg > 1 && ft_check_arg_exit(exec))
		ret = 2;
	else if (nb_arg > 2)
	{
		ft_putstr_fd("minipouet: ", 2);
		ft_putstr_fd(exec->cmd_array[0], 2);
		ft_putstr_fd(": too many arguments\n", 2);
		return (1);
	}
	if (!ret && nb_arg == 2 && exec->cmd_array[1] && exec->cmd_array[1][0])
		ret = ft_atoi(exec->cmd_array[1]);
	else if (!ret)
		ret = exec->infos->exit_val;
	ft_clean_end_builtin(exec, fd_pipe, ret, 1);
	return (1);
}
