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

static void	ft_reset_fd_pipe(int fd_pipe[2])
{
	fd_pipe[0] = -1;
	fd_pipe[1] = -1;
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
			return (ft_err_exc("minipouet", ERROR_PIPE, nw, fdp));
		if (ft_fork_and_child(&id, nw, fdp))
			return (ft_err_exc("minipouet", ERROR_FORK, nw, fdp));
		if (nw != nw->head && ft_close(&(nw->files->infile->fd), nw, fdp) == -1)
			return (ft_err_exc("minipouet", ERROR_CLOSE, nw, fdp));
		if (nw->next != NULL && ft_close(&fdp[1], nw, fdp) == -1)
			return (ft_err_exc("minipouet", ERROR_CLOSE, nw, fdp));
		if (nw->next != NULL)
			nw->next->files->infile->fd = fdp[0];
		nw = nw->next;
		*last = id;
	}
	return (0);
}

static int	ft_signaled(t_exec *lst, pid_t last, pid_t tmp, int status)
{
	int	sig;

	sig = WTERMSIG(status);
	if (last == tmp)
		lst->infos->exit_val = 128 + sig;
	return (sig);
}

static void	ft_end_main_exec(int exec_ret, t_exec *lst, int sig)
{
	if (sig == SIGINT)
		write (1, "\n", 1);
	if (exec_ret <= ERROR_EXEC)
		lst->infos->exit_val = 1;
	ft_clean_end_exec(lst);
}

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
			sig = ft_signaled(lst, last, tmp, status);
		tmp = wait(&status);
	}
	ft_end_main_exec(exec_ret, lst, sig);
}
