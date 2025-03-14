/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <aibonade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:05:20 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/13 14:40:56 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_clean_end_builtin(t_exec *exec, int fd_pipe[2], int ret, int child)//met exec pas exec->head
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
	if (child)
	{
		ft_free_infos(exec->infos, 0, 0);
		ft_clean_end_exec(exec_head);
		exit(ret);
	}
	return (ret);
}

int	ft_builtin(t_exec *exec, int fd_pipe[2], int child)
{
	int	std_fd;//1 = in 2 = out 3 = in + out
	int	ret_val;

	std_fd = 0;
	if (exec->files->infile->fd == -1)//Du coup on les ferme en cas d'erreur...
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
		ret_val = ft_cd(exec, fd_pipe, child, std_fd);//Aileen
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
		exec->infos->exit_val = ft_env(exec->infos, exec, exec->files->outfile);
	else if (exec->builtin == EXIT)
	{
		;//Aileen
	}
	if (std_fd == 1 || std_fd == 3)//jouer avec les param de clean end builtin si on doit virer ces 4 lignes
		exec->files->infile->fd = -1;
	if (std_fd == 2 || std_fd == 3)
		exec->files->outfile->fd = -1;
	return (ft_clean_end_builtin(exec, fd_pipe, ret_val, child));
}