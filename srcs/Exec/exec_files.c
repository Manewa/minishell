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

int ft_close(int fd, t_exec *data, int fd_pipe[2])
{
	if (close(fd) == -1)
	{
		ft_error_close(fd, data, fd_pipe);
		return (-1);
	}
	//mettre fd a -1 pour tout close correctement ?
	return (0);
}

void ft_open_infile(int fd_pipe[2], t_exec *exc, t_lim *hd, t_fdata *infile)//Error avec exit
{
	//OUVERTS : Infile (fdp-1[0], si exc != exc->head), fdp[0]*, fdp[1]* (*si one->next != NULL)
	if (exc->is_heredoc > 0
			&& ft_set_heredoc(exc->is_heredoc, hd, infile, fd_pipe) < 0)//MODIFIE
	{
		exit(ERROR_EXEC);//ERROR
	}
	if (infile->heredoc == NO || infile->heredoc == YES)//No = redir YES = heredoc
	{
		if (exc != exc->head)
		{
			if(ft_close(infile->fd, exc, fd_pipe) == -1)
				exit(ERROR_EXEC);//ERROR
		}
		infile->fd = open(infile->name, O_RDONLY);
		if (infile->fd == -1)
		{
			exit(ERROR_EXEC);//ft_error_exec("Open output file is impossible.", data, fd_pipe);
		}
	}
}

void ft_open_outfile(int fd_pipe[2], t_exec *exec, t_fdata *outfile)//Error avec exit
{
	if (outfile->name != NULL)//= Redirection
	{
		if (exec->next != NULL)
		{
			if(ft_close(fd_pipe[1], exec, fd_pipe) == -1)
				exit(ERROR_EXEC);//ERROR
		}
		outfile->fd = open(outfile->name, O_WRONLY | O_APPEND);
		if (outfile->fd == -1)
		{
			exit(ERROR_EXEC);//ft_error_exec("Open output file is impossible.", data, fd_pipe);
		}
	}
	else if (exec->next != NULL)
		outfile->fd = fd_pipe[1];
}
