/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:57:54 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/28 17:06:47 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_set_heredoc_name(unsigned long i_heredoc)
{
	char	*h_name;
	char	*str_i;

	str_i = ft_ultoa(i_heredoc);
	h_name = ft_strjoin("/tmp/.heredoc", str_i);
	free(str_i);
	if (access(h_name, F_OK) != -1)
	{
		free(h_name);
		if (i_heredoc < 4294967295)
			h_name = ft_set_heredoc_name(i_heredoc + 1);
		else
		{
			errno = EAGAIN;
			return (NULL);
		}
	}
	errno = 0;
	return (h_name);
}

static int	ft_fill_check_hd(t_exec *exec, t_lim *tmp, int *fd, int fdp[2])
{
	int	ret_fill;

	ret_fill = ft_fill_heredoc(exec->infos, tmp, *fd);
	if (ret_fill)
	{
		ft_close(fd, exec, fdp);
		unlink(tmp->h_name);
		return (ft_err_exc("minipouet", ret_fill, exec, fdp));
	}
	return (0);
}

static int	ft_close_sethd(t_exec *exec, int *fd, int fdp[2], char *tmp_file)
{
	if (ft_close(fd, exec, fdp) == -1)
	{
		unlink(tmp_file);
		return (ft_err_exc("minipouet", ERROR_HEREDOC, exec, fdp));
	}
	return (0);
}

static int	ft_open_fill_and_close(t_exec *exec, t_lim *tmp, int fdp[2])
{
	int	ret;
	int	fd;

	fd = open(tmp->h_name, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (fd == -1)
		return (ft_err_exc("minipouet", ERROR_HEREDOC, exec, fdp));
	ret = ft_fill_check_hd(exec, tmp, &fd, fdp);
	if (ret)
		return (ret);
	ret = ft_close_sethd(exec, &fd, fdp, tmp->h_name);
	if (ret)
		return (ret);
	return (0);
}

int	ft_sethd(t_exec *exec, t_lim *hd, t_fdata *infile, int fdp[2])
{
	t_lim			*tmp;
	unsigned long	i;
	int				nb_lim;
	int				ret;

	tmp = hd;
	i = 0;
	nb_lim = exec->is_heredoc + 1;
	while (--nb_lim)
	{
		tmp->h_name = ft_set_heredoc_name(i++);
		if (!tmp->h_name)
			return (ft_err_exc("minipouet: heredoc", ERROR_HEREDOC, exec, fdp));
		if (nb_lim == 1 && infile->heredoc == YES)
			infile->name = tmp->h_name;
		ret = ft_open_fill_and_close(exec, tmp, fdp);
		if (ret)
			return (ret);
		if ((nb_lim > 1 || infile->heredoc != YES) && unlink(tmp->h_name) == -1)
			return (ft_err_exc("minipouet", ERROR_HEREDOC, exec, fdp));
		tmp = tmp->next;
	}
	return (0);
}
