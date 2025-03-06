/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <aibonade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:45:49 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/06 16:49:20 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_error_exec(char *perror_str, int ret_val, t_exec *current, int fd_pipe[2])//, int exit)
{
	perror(perror_str);
	//potentiellement des fork deja reussi => wait dans le main_exec
	//exec a free => dans le main_exec
	if (current != current->head)//pipe -1 ouvert =>infile de exec
	{
		if (ret_val == ERROR_PIPE)
		{
			fd_pipe[0] = -1;
			fd_pipe[1] = -1;
		}
		if (ft_close(current->files->infile->fd, current, fd_pipe) == -1)
			return(ret_val);//ERROR_CLOSE ?
	}
	if (ret_val == ERROR_FORK)
	{
		if (current->next)//pipe ouvert (sauf si dernier node)
		{
			if (ft_close(fd_pipe[0], current, fd_pipe) != -1)
				ft_close(fd_pipe[1], current, fd_pipe);
		}
	}
	return (ret_val);
}

void ft_error_child(t_exec *data, int fd_pipe[2])//(char *msg, t_data *data, int fd_pipe[2])
{
	if (fd_pipe[0] > -1)
	{
		ft_close(fd_pipe[0], data, fd_pipe);
	}
	if (fd_pipe[1] > -1)
	{
		ft_close(fd_pipe[1], data, fd_pipe);
	}
	ft_clean_end_exec(data);
	//ft_putstr_error(msg);
	exit(ERROR_EXEC);
}

void ft_error_close(int fd, t_exec *data, int fd_pipe[2])
{
	if (fd == fd_pipe[0])
		fd_pipe[0] = -1;
	else if (fd == fd_pipe[1])
		fd_pipe[1] = -1;
	if (fd_pipe[0] > -1)
	{
		ft_close(fd_pipe[0], data, fd_pipe);
		fd_pipe[0] = -1;
	}
	if (fd_pipe[1] > -1)
	{
		ft_close(fd_pipe[1], data, fd_pipe);
		fd_pipe[1] = -1;
	}
	ft_putstr_fd("Close error.\n", 2);//A adapter
}
