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
	perror(perror_str);//pas forcement utile perror_str => ici ce sera forcement minipouet
	//potentiellement des fork deja reussi => wait dans le main_exec
	//exec a free => dans le main_exec
	if (current != current->head)//pipe -1 ouvert =>infile de exec
	{
		if (ret_val == ERROR_PIPE)
		{
			fd_pipe[0] = -1;
			fd_pipe[1] = -1;
		}
		if (ft_close(&(current->files->infile->fd), current, fd_pipe) == -1)
			return(ret_val);//ERROR_CLOSE ?
	}
	if (ret_val == ERROR_FORK)
	{
		if (current->next)//pipe ouvert (sauf si dernier node)
		{
			if (ft_close(&fd_pipe[0], current, fd_pipe) != -1)
				ft_close(&fd_pipe[1], current, fd_pipe);
		}
	}
	return (ret_val);
}

void ft_error_child(t_exec *exec, int fd_pipe[2], int *fd_to_close)
{
	t_exec	*exec_head;

perror("child");
	exec_head = exec->head;
	if (exec->files->infile->fd > -1)
		ft_close(&(exec->files->infile->fd), exec_head, fd_pipe);
	if (fd_to_close && *fd_to_close > -1)
		ft_close(fd_to_close, exec_head, fd_pipe);
	if (fd_pipe[0] > -1)
	{
		ft_close(&fd_pipe[0], exec_head, fd_pipe);
	}
	if (fd_pipe[1] > -1)
	{
		ft_close(&fd_pipe[1], exec_head, fd_pipe);
	}
	ft_clean_end_exec(exec_head);
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
		ft_close(&fd_pipe[0], data, fd_pipe);
		fd_pipe[0] = -1;//plus utile avec ft_close
	}
	if (fd_pipe[1] > -1)
	{
		ft_close(&fd_pipe[1], data, fd_pipe);
		fd_pipe[1] = -1;//plus utile avec ft_close
	}
	ft_putstr_fd("Close error.\n", 2);//A virer
}
