/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <aibonade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:45:49 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/28 17:15:28 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_err_exc(char *perr_str, int ret, t_exec *current, int fd_pipe[2])
{
	if (ret != 130)
		perror(perr_str);
	if (current != current->head)
	{
		if (ret == ERROR_PIPE)
		{
			fd_pipe[0] = -1;
			fd_pipe[1] = -1;
		}
		if (ft_close(&(current->files->infile->fd), current, fd_pipe) == -1)
			return (ret);
	}
	if (ret == ERROR_FORK || ret == ERROR_HEREDOC)
	{
		if (current->next)
		{
			if (ft_close(&fd_pipe[0], current, fd_pipe) != -1)
				ft_close(&fd_pipe[1], current, fd_pipe);
		}
	}
	return (ret);
}

int	ft_put_error_files(t_exec *exec, int ret_val)
{
	ft_putstr_fd("minipouet: ", 2);
	if (ret_val == ERROR_INFILE)
		perror(exec->files->infile->name);
	else
		perror(exec->files->outfile->name);
	return (1);
}

void	ft_error_child(t_exec *exc, int fd_pipe[2], int *to_close, int ret_val)
{
	t_exec	*exec_head;

	if (ret_val == ERROR_NF)
		ret_val = 127;
	else if (ret_val == ERROR_INFILE || ret_val == ERROR_OUTFILE)
		ret_val = ft_put_error_files(exc, ret_val);
	else
		perror(exc->cmd_array[0]);
	exec_head = exc->head;
	if (exc->files->infile->fd > -1)
		ft_close(&(exc->files->infile->fd), exec_head, fd_pipe);
	if (to_close && *to_close > -1)
		ft_close(to_close, exec_head, fd_pipe);
	if (fd_pipe[0] > -1)
		ft_close(&fd_pipe[0], exec_head, fd_pipe);
	if (fd_pipe[1] > -1)
		ft_close(&fd_pipe[1], exec_head, fd_pipe);
	ft_lstenvfree(exec_head->infos->env);
	ft_free_infos(exec_head->infos, 0, 0);
	free(exec_head->infos);
	ft_clean_end_exec(exec_head);
	exit(ret_val);
}

void	ft_error_close(int fd, t_exec *data, int fd_pipe[2])
{
	if (fd == fd_pipe[0])
		fd_pipe[0] = -1;
	else if (fd == fd_pipe[1])
		fd_pipe[1] = -1;
	if (fd_pipe[0] > -1)
		ft_close(&fd_pipe[0], data, fd_pipe);
	if (fd_pipe[1] > -1)
		ft_close(&fd_pipe[1], data, fd_pipe);
}
