/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:09:25 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/30 16:09:28 by aibonade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_dup2(int *old, int nw, int fd_pipe[2], t_exec *lst)
{
	int	tmp;

	tmp = nw;
	if (ft_close(&tmp, lst, fd_pipe) == -1)
		ft_error_child(lst, fd_pipe, old, 1);
	if (dup2(*old, nw) == -1)
		ft_error_child(lst, fd_pipe, old, 1);
	if (ft_close(old, lst, fd_pipe) == -1)
		ft_error_child(lst, fd_pipe, old, 1);
}

static void	ft_error_126(t_exec *exec, int fd_pipe[2], int error)
{
	ft_putstr_fd("minipouet: ", 2);
	errno = error;
	ft_error_child(exec, fd_pipe, &(exec->files->outfile->fd), 126);
}

static void	ft_check_access(t_exec *exec, int fd_pipe[2])
{
	int			i;
	struct stat	f_infos;

	i = 0;
	while (exec->cmd_path[i] && exec->cmd_path[i] != '/')
		i++;
	if (!exec->cmd_path[i] || !exec->cmd_array[0][0])
	{
		ft_putstr_fd("minipouet: ", 2);
		ft_putstr_fd(exec->cmd_array[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_error_child(exec, fd_pipe, &(exec->files->outfile->fd), ERROR_NF);
	}
	if (stat(exec->cmd_path, &f_infos) == -1)
		ft_error_child(exec, fd_pipe, &(exec->files->outfile->fd), 127);
	if (exec->cmd_path && !S_ISDIR(f_infos.st_mode))
	{
		if (access(exec->cmd_path, X_OK))
			ft_error_126(exec, fd_pipe, EACCES);
	}
	else
		ft_error_126(exec, fd_pipe, EISDIR);
}

static void	ft_child(int fd_pipe[2], t_exec *one)
{
	ft_open_infile(fd_pipe, one, one->files->infile, 1);
	if (one != one->head || one->files->infile->heredoc != NO_INFO)
		ft_dup2(&(one->files->infile->fd), STDIN_FILENO, fd_pipe, one->head);
	if (one->next != NULL)
		if (ft_close(&fd_pipe[0], one, fd_pipe) == -1)
			ft_error_child(one, fd_pipe, NULL, 1);
	ft_open_outfile(fd_pipe, one, one->files->outfile, 1);
	if (one->next != NULL || one->files->outfile->name)
	{
		ft_dup2(&(one->files->outfile->fd), STDOUT_FILENO, fd_pipe, one->head);
		fd_pipe[1] = -1;
	}
	if (one->cmd_array && one->cmd_array[0])
	{
		if (one->builtin)
			ft_builtin(one, fd_pipe, 1);
		ft_check_access(one, fd_pipe);
		execve(one->cmd_path, one->cmd_array, one->env);
		ft_error_child(one, fd_pipe, &(one->files->outfile->fd), 1);
	}
	ft_lstenvfree(one->infos->env);
	ft_free_infos(one->infos, 0, 0);
	free(one->infos);
	ft_clean_end_exec(one->head);
	exit(0);
}

int	ft_fork_and_child(pid_t *id, t_exec *now, int fd_pipe[2])
{
	signal(SIGINT, SIG_IGN);
	*id = fork();
	if (*id == -1)
		return (1);
	if (*id == 0)
	{
		set_signal(now->infos);
		ft_child(fd_pipe, now);
	}
	return (0);
}
