/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:30:52 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/29 14:59:50 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_sig;

static void	ft_dup2(int *old, int new, int fd_pipe[2], t_exec *lst)
{
	int	tmp;

	tmp = new;
	if (ft_close(&tmp, lst, fd_pipe) == -1)
		ft_error_child(lst, fd_pipe, old, 1);
	if (dup2(*old, new) == -1)
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

static void	ft_reset_fd_pipe(int fd_pipe[2])
{
	fd_pipe[0] = -1;
	fd_pipe[1] = -1;
}

static int	ft_fork_and_child(pid_t *id, t_exec *now, int fd_pipe[2])
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

static int	ft_exec(t_exec *lst, pid_t *last)
{
	int		fdp[2];
	pid_t	id;
	t_exec	*nw;

	nw = lst->head;
	while (nw)
	{
		ft_reset_fd_pipe(fdp);
		if (nw->is_heredoc && ft_sethd(nw, nw->limiter, nw->files->infile, fdp))
			return (ERROR_HEREDOC);
		if ((nw->next != NULL) && (pipe(fdp) == -1))
			return (ft_error_exec("minipouet", ERROR_PIPE, nw, fdp));
		if (ft_fork_and_child(&id, nw, fdp))
			return (ft_error_exec("minipouet", ERROR_FORK, nw, fdp));
		if (nw != nw->head && ft_close(&(nw->files->infile->fd), nw, fdp) == -1)
			return (ft_error_exec("minipouet", ERROR_CLOSE, nw, fdp));
		if (nw->next != NULL && ft_close(&fdp[1], nw, fdp) == -1)
			return (ft_error_exec("minipouet", ERROR_CLOSE, nw, fdp));
		if (nw->next != NULL)
			nw->next->files->infile->fd = fdp[0];
		nw = nw->next;
		*last = id;
	}
	return (0);
}
//124

void	ft_main_exec(t_exec *lst)
{
	int		exec_ret;
	pid_t	last;
	pid_t	tmp;
	int		status;
	int		sig;

	errno = 0;
	exec_ret = 0;
	sig = 0;
	if ((lst->builtin == CD || lst->builtin == EXPORT
			|| lst->builtin == EXIT || lst->builtin == UNSET) && !lst->next)
		lst->infos->exit_val = ft_main_builtin_parent(lst);
	else
		exec_ret = ft_exec(lst, &last);
	tmp = wait(&status);
	while (tmp > 0)
	{
		if (WIFEXITED(status) && last == tmp)
			lst->infos->exit_val = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (last == tmp)
				lst->infos->exit_val = 128 + sig;
		}
		tmp = wait(&status);
	}
	if (sig == SIGINT)
		write (1, "\n", 1);
	if (exec_ret <= ERROR_EXEC)
		lst->infos->exit_val = 1;
	ft_clean_end_exec(lst);
}
//163
