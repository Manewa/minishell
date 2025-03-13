/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <aibonade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:05:20 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/13 11:05:26 by aibonade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_clean_end_builtin(t_exec *exec, int fd_pipe[2])//met exec pas exec->head
{
	t_exec	*exec_head;

	exec_head = exec->head;
	if (exec->files->infile->fd > -1)
		ft_close(&(exec->files->infile->fd), exec_head, fd_pipe);
	if (exec->files->outfile->fd > -1)
		ft_close(&(exec->files->outfile->fd), exec_head, fd_pipe);
	if (fd_pipe[0] > -1)
	{
		ft_close(&fd_pipe[0], exec_head, fd_pipe);
	}
	if (fd_pipe[1] > -1)
	{
		ft_close(&fd_pipe[1], exec_head, fd_pipe);
	}
	ft_free_infos(exec->infos, 0, 0);
	ft_clean_end_exec(exec_head);
	exit(0);
}

void	ft_builtin(t_exec *exec, int fd_pipe[2])
{
	int	std_fd;//1 = in 2 = out 3 = in + out

	std_fd = 0;
	if (exec->files->infile->fd == -1)
	{
		std_fd = 1;
		exec->files->infile->fd = STDIN_FILENO;
	}
	if (exec->files->outfile->fd == -1)
	{
		std_fd += 2;
		exec->files->outfile->fd = STDOUT_FILENO;
	}
	if (exec->builtin == ECHO)
	{
		;
	}
	else if (exec->builtin == CD)
	{
		;//ft_cd(exec, fd_pipe);//Aileen
	}
	else if (exec->builtin == PWD)
	{
		;//Aileen
	}
	else if (exec->builtin == EXPORT)
	{
		;//Nathan
	}
	else if (exec->builtin == UNSET)
	{
		;//Nathan
	}
	else if (exec->builtin == ENV)
	{
		;//Nathan
	}
	else if (exec->builtin == EXIT)
	{
		;//Aileen
	}
	if (std_fd == 1 || std_fd == 3)//jouer avec les param de clean end builtin si on doit virer ces 4 lignes
		exec->files->infile->fd = -1;
	if (std_fd == 2 || std_fd == 3)
		exec->files->outfile->fd = -1;
	ft_clean_end_builtin(exec, fd_pipe);
}