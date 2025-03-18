/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <aibonade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:05:20 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/17 15:48:04 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_clean_end_builtin(t_exec *exec, int fd_pipe[2], int ret, int exit_proc)//met exec pas exec->head
{
	t_exec	*exec_head;

	exec_head = exec->head;
	if (exec->files->infile->fd > -1)
		ft_close(&(exec->files->infile->fd), exec_head, fd_pipe);
	if (exec->files->outfile->fd > -1)
		ft_close(&(exec->files->outfile->fd), exec_head, fd_pipe);
	if (fd_pipe[0] > -1)
		ft_close(&fd_pipe[0], exec_head, fd_pipe);
	if (fd_pipe[1] > -1)
		ft_close(&fd_pipe[1], exec_head, fd_pipe);
	if (exit_proc)
	{
		ft_free_infos(exec->infos, 0, 0);
		ft_clean_end_exec(exec_head);
		exit(ret);
	}
	return (ret);
}

static int	ft_set_stdfd(t_exec *exec)
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
	return (std_fd);
}

int	ft_builtin(t_exec *exec, int fd_pipe[2], int child)
{
	int	ret_val;
	int	std_fd;

	std_fd = ft_set_stdfd(exec);
	if (exec->builtin == ECHO)
		ret_val = ft_echo(exec);
	else if (exec->builtin == CD)
		ret_val = ft_cd(exec, fd_pipe, child, std_fd);
	else if (exec->builtin == PWD)
		ret_val = ft_pwd(exec);
	else if (exec->builtin == EXPORT)
		ret_val = ft_export(exec, exec->files->outfile->fd);
	else if (exec->builtin == UNSET)
		ret_val = ft_unset(exec, exec->files->outfile->fd); 
	else if (exec->builtin == ENV)
		ret_val = ft_env(exec->infos, exec, exec->files->outfile);
	else if (exec->builtin == EXIT)
		ret_val = ft_exit(exec, fd_pipe);
	if (std_fd == 1 || std_fd == 3)
		exec->files->infile->fd = -1;
	if (std_fd == 2 || std_fd == 3)
		exec->files->outfile->fd = -1;
	return (ft_clean_end_builtin(exec, fd_pipe, ret_val, child));
}

int	ft_main_builtin_parent(t_exec *exec)
{
	int		fd_pipe[2];

	fd_pipe[0] = -1;
	fd_pipe[1] = -1;
	//gerer les redir
	if (exec->is_heredoc)
	{
		if (ft_set_heredoc(exec, exec->limiter, exec->files->infile, fd_pipe))
			return (ft_clean_end_builtin(exec, fd_pipe, ERROR_HEREDOC,  0));
	}
	if (ft_open_infile(fd_pipe, exec, exec->files->infile, 0))//ouvrir l'infile si besoin et eventuellement fermer la lecture du pipe-1[0]
		return (ft_clean_end_builtin(exec, fd_pipe, 1,  0));
	if (ft_open_outfile(fd_pipe, exec, exec->files->outfile, 0))
		return (ft_clean_end_builtin(exec, fd_pipe, 1,  0));
	return (ft_builtin(exec, fd_pipe, 0));
}
