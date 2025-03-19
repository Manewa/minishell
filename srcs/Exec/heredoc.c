/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:57:54 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/19 12:27:40 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	sig_global;

static char	*ft_set_heredoc_name(unsigned long i_heredoc)
{
	char	*h_name;
	char	*str_i;

	str_i = ft_ultoa(i_heredoc);
	h_name = ft_strjoin("/tmp/.heredoc", str_i);//a modifier selon l'endroit ou on mettra les tmps
	free(str_i);
	if (access(h_name, F_OK) != -1)
	{
		free(h_name);
		if (i_heredoc < 4294967295)//faire du unsigned long long ? : 18446744073709551615
			h_name = ft_set_heredoc_name(i_heredoc + 1);
		else
		{
			errno = EAGAIN;//ft_putstr_fd("ERROR: create heredoc is impossible.\n", 2);//ERROR
			return (NULL);
		}
	}
	errno = 0;//utile ?
	return (h_name);
}


static int	ft_fill_heredoc(t_infos *infos, t_lim *heredoc, int fd, int fd_pipe[2])//dans les child, voir set_heredoc
{
	char	*line;
	char	*lim;
	int		nb_line;

//fd_pipe pour les signaux & gestion d'erreur
	(void)fd_pipe;//A Supprimer une fois implemente !!!!!!!!! (pouet)
	nb_line = 0;
	lim = heredoc->limit;
	define_signal(SIGINT, &sig_handler_hd_c, infos); 
	line = readline("> ");
	if (sig_global == SIGINT_HD)
		return (130);
	while (line && ft_strncmp(line, lim, ft_strlen(lim) + 1))
	{
		nb_line++;
		if (heredoc->quotes == NO)
		{
			line = expand_main_heredoc(line, infos);//line = ft_expand pour les var uniquement...
			if (!line)
				return (ERROR_HEREDOC);
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
		line = readline("> ");
		if (!line && sig_global != SIGINT_HD)//A checker : ctrl D n'est a gerer que pour exit du shell normalement
			printf("minipouet: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", nb_line, heredoc->h_name);
		else if (sig_global == SIGINT_HD)
			return (130);
	}
	if (line)
		free(line);
	return (0);
}

int	ft_set_heredoc(t_exec *exec, t_lim *hd, t_fdata *infile, int fdpipe[2])
{
	t_lim			*tmp;
	unsigned long	i;
	int				nb_lim;
	int				fd;
	int				ret_fill;

	tmp = hd;
	i = 0;
	nb_lim = exec->is_heredoc;
	while (nb_lim)
	{
		tmp->h_name = NULL;//utile ? 
		tmp->h_name = ft_set_heredoc_name(i);
		if (!tmp->h_name)
			return (ft_error_exec("minipouet: heredoc", ERROR_HEREDOC, exec, fdpipe));
		if (nb_lim == 1 && infile->heredoc == YES)
			infile->name = tmp->h_name;
		fd = open(tmp->h_name, O_WRONLY | O_TRUNC | O_CREAT, 0664);
		if (fd == -1)
			return (ft_error_exec("minipouet", ERROR_HEREDOC, exec, fdpipe));//minipouet ou pouetsh ?
		ret_fill = ft_fill_heredoc(exec->infos, tmp, fd, fdpipe);
		if (ret_fill)
		{
			ft_close(&fd, exec, fdpipe);
			unlink(tmp->h_name);
			return (ft_error_exec("minipouet", ret_fill, exec, fdpipe));
		}
		if (ft_close(&fd, exec, fdpipe) == -1)
		{
			unlink(tmp->h_name);
			return (ft_error_exec("minipouet", ERROR_HEREDOC, exec, fdpipe));
		}
		if (nb_lim > 1 || infile->heredoc != YES)
		{
			if (unlink(tmp->h_name) == -1)
				return (ft_error_exec("minipouet", ERROR_HEREDOC, exec, fdpipe));
		}
		tmp = tmp->next;
		nb_lim--;
		i++;
	}
	return (0);
}
