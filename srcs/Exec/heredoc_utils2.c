/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:31:06 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/30 16:31:09 by aibonade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_sig;

void	ft_free_dbltab(char **str)
{
	size_t	i;

	if (str)
	{
		i = 0;
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

static int	ft_readline(char **line, int nbl, int dup_tmp, char *lim)
{
	*line = readline("> ");
	if (!(*line) && g_sig != SIGINT_HD)
	{
		ft_putstr_fd("minipouet: warning: here-document at line ", 1);
		printf("%d delimited by end-of-file (wanted `%s')\n", nbl, lim);
	}
	else if (g_sig == SIGINT_HD)
	{
		dup2(dup_tmp, STDIN_FILENO);
		close(dup_tmp);
		return (130);
	}
	return (0);
}

static int	ft_expand_line(char **line, t_infos *infos, t_lim *heredoc)
{
	if (heredoc->quotes == NO)
	{
		*line = expand_main_heredoc(*line, infos);
		if (!line)
			return (ERROR_HEREDOC);
	}
	return (0);
}

int	ft_fill_heredoc(t_infos *infos, t_lim *heredoc, int fd)
{
	char	*line;
	char	*lim;
	int		nb_line;
	int		dup_tmp;

	nb_line = 1;
	lim = heredoc->limit;
	dup_tmp = dup(STDIN_FILENO);
	define_signal(SIGINT, &sig_handler_hd_c, infos);
	if (ft_readline(&line, nb_line, dup_tmp, heredoc->limit))
		return (130);
	while (line && ft_strncmp(line, lim, ft_strlen(lim) + 1))
	{
		nb_line++;
		if (ft_expand_line(&line, infos, heredoc))
			return (ERROR_HEREDOC);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
		if (ft_readline(&line, nb_line, dup_tmp, heredoc->limit))
			return (130);
	}
	if (line)
		free(line);
	return (close(dup_tmp), 0);
}
