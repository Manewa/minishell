/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <aibonade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:43:03 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/29 14:54:43 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_close(int *fd, t_exec *data, int fd_pipe[2])
{
	if (*fd != -1 && close(*fd) == -1)
	{
		ft_error_close(*fd, data, fd_pipe);
		return (-1);
	}
	*fd = -1;
	return (0);
}

//infile->heredoc != NO_INFO (NO = redir YES = heredoc) => redir
int	ft_open_infile(int fd_pipe[2], t_exec *exc, t_fdata *infile, int child)
{
	if (infile->heredoc == NO || infile->heredoc == YES)
	{
		if (exc != exc->head)
		{
			if (ft_close(&(infile->fd), exc, fd_pipe) == -1)
			{
				if (child)
					ft_error_child(exc, fd_pipe, NULL, ERROR_INFILE);
				ft_putstr_fd("minipouet: ", 2);
				perror(infile->name);
				return (1);
			}
		}
		infile->fd = open(infile->name, O_RDONLY);
		if (infile->fd == -1)
		{
			if (child)
				ft_error_child(exc, fd_pipe, NULL, ERROR_INFILE);
			ft_putstr_fd("minipouet: ", 2);
			perror(infile->name);
			return (1);
		}
	}
	return (0);
}

int	ft_open_outfile(int fd_pipe[2], t_exec *exec, t_fdata *out, int child)
{
	if (out->name != NULL)
	{
		if (exec->next != NULL && (ft_close(&fd_pipe[1], exec, fd_pipe) == -1))
		{
			if (child)
				ft_error_child(exec, fd_pipe, NULL, ERROR_OUTFILE);
			ft_putstr_fd("minipouet: ", 2);
			perror(out->name);
			return (1);
		}
		out->fd = open(out->name, O_WRONLY | O_APPEND);
		if (out->fd == -1)
		{
			if (child)
				ft_error_child(exec, fd_pipe, NULL, ERROR_OUTFILE);
			ft_putstr_fd("minipouet: ", 2);
			perror(out->name);
			return (1);
		}
	}
	else if (exec->next != NULL)
		out->fd = fd_pipe[1];
	return (0);
}
