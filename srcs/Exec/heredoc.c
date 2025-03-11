/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:57:54 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/06 16:54:47 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_set_heredoc_name(unsigned long i_heredoc)
{
	char	*h_name;
	char	*str_i;

	str_i = ft_ultoa(i_heredoc);
	h_name = ft_strjoin(".heredoc", str_i);//a modifier selon l'endroit ou on mettra les tmps
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


static void	ft_fill_heredoc(t_lim *heredoc, int fd, int fd_pipe[2])//dans les child, voir set_heredoc
{
	char	*line;
	char	*lim;

//fd_pipe pour les signaux & gestion d'erreur
	(void)fd_pipe;//A Supprimer une fois implemente !!!!!!!!! (pouet)
	lim = heredoc->limit;
	line = readline("> ");

	while (line && ft_strncmp(line, lim, ft_strlen(lim) + 1))
	{
		if (heredoc->quotes == NO)
		{
			;//line = ft_expand pour les var uniquement...
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
		line = readline("> ");
		if (!line)//A checker : ctrl D n'est a gerer que pour exit du shell normalement
			ft_putstr_fd("Avertissement car EOF et pas limiter (ferme avec ctrl+D et pas mot-clef), mais la suite s'exécute bien.\n", 1);//a reformuler
	}
	if (line)
		free(line);
}

void	ft_set_heredoc(t_exec *exec, t_lim *hd, t_fdata *infile, int fdpipe[2])
{
	t_lim			*tmp;
	unsigned long	i;
	int				nb_lim;
	int				fd;

	tmp = hd;
	i = 0;
	nb_lim = exec->is_heredoc;
	while (nb_lim)
	{
		tmp->h_name = NULL;//utile ? 
		tmp->h_name = ft_set_heredoc_name(i);
		if (!tmp->h_name)
		{
			ft_error_exec("minipouet: heredoc", ERROR_HEREDOC, exec, fdpipe);//checker avec Nathan
			return ;
		}
		if (nb_lim == 1 && infile->heredoc == YES)
			infile->name = tmp->h_name;
		fd = open(tmp->h_name, O_WRONLY | O_TRUNC | O_CREAT, 0664);
		if (fd == -1)
		{
			ft_error_exec("minipouet", ERROR_HEREDOC, exec, fdpipe);
			return ;
		}
		else
			ft_fill_heredoc(tmp, fd, fdpipe);
		if (ft_close(&fd, exec, fdpipe) == -1)
		{
			ft_error_exec("minipouet", ERROR_HEREDOC, exec, fdpipe);
			return ;
		}
		if (nb_lim > 1 || infile->heredoc != YES)
		{
			if (unlink(tmp->h_name) == -1)
			{
				ft_error_exec("minipouet", ERROR_HEREDOC, exec, fdpipe);
				return ;
			}
		}
		tmp = tmp->next;
		nb_lim--;
		i++;
	}
}
