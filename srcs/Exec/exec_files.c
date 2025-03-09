/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <aibonade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:43:03 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/06 16:16:50 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_close(int *fd, t_exec *data, int fd_pipe[2])
{
	if (*fd != -1 && close(*fd) == -1)
	{
		ft_error_close(*fd, data, fd_pipe);
		return (-1);
	}
	*fd = -1;//mettre fd a -1 pour tout close correctement ?
	return (0);
}

void ft_open_infile(int fd_pipe[2], t_exec *exc, t_lim *hd, t_fdata *infile)//Error avec exit
{
	(void)hd;//a virer
	// if (exc->is_heredoc > 0
	// 		&& ft_set_heredoc(exc->is_heredoc, hd, infile, fd_pipe) < 0)//MODIFIE
	// {
	// 	ft_error_child(exc, fd_pipe, NULL);
	// }
	if (infile->heredoc == NO || infile->heredoc == YES)//donc != NO_INFO (NO = redir YES = heredoc)
	{
		if (exc != exc->head)
		{
			if(ft_close(&(infile->fd), exc, fd_pipe) == -1)
				ft_error_child(exc, fd_pipe, NULL, NULL);
		}
		infile->fd = open(infile->name, O_RDONLY);
		if (infile->fd == -1)
			ft_error_child(exc, fd_pipe, NULL, NULL);
	}
}

void ft_open_outfile(int fd_pipe[2], t_exec *exec, t_fdata *outfile)//Error avec exit
{
	if (outfile->name != NULL)//= Redirection
	{
		if (exec->next != NULL)
		{
			if(ft_close(&fd_pipe[1], exec, fd_pipe) == -1)
				ft_error_child(exec, fd_pipe, NULL, NULL);
		}
		outfile->fd = open(outfile->name, O_WRONLY | O_APPEND);
		if (outfile->fd == -1)
		{
			ft_error_child(exec, fd_pipe, NULL, NULL);;//ft_error_exec("Open output file is impossible.", data, fd_pipe);
		}
	}
	else if (exec->next != NULL)
		outfile->fd = fd_pipe[1];
}
