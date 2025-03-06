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
	int		fd;

	str_i = ft_ultoa(i_heredoc);
	h_name = ft_strjoin("tmp/.heredoc", str_i);//a modifier selon l'endroit ou on mettra les tmps
	free(str_i);
	if (access(h_name, F_OK) != -1)//attention maj de errno :/
	{
		free(h_name);
		if (i_heredoc < 4294967295)//faire du unsigned long long ? : 18446744073709551615
			h_name = ft_set_heredoc_name(i_heredoc + 1);
		else
		{
			ft_putstr_fd("ERROR: create heredoc is impossible.\n", 2);//ERROR
			return (NULL);
		}
	}
	else
	{
		fd = open(h_name, O_WRONLY | O_TRUNC | O_CREAT, 0664);//creer le fichier pour que les suivants ne le tentent pas
		if (fd == -1)
			ft_putstr_fd("ERROR: Open here_doc file is impossible.\n", 2);//ERROR
		close(fd);
	}
	return (h_name);
}

void	ft_check_heredoc(int nb_lim, t_lim *heredoc, t_fdata *infile)//A faire avant de lancer les processus (pour checker les noms)
{
	t_lim			*tmp;
	unsigned long	i;

	tmp = heredoc;
	i = 0;
	while (nb_lim)
	{
		tmp->h_name = NULL;//checker si c'est utile ? 
		tmp->h_name = ft_set_heredoc_name(i);//ERROR Si NULL parce que erreur comportement 
		if (nb_lim == 1 && infile->heredoc == YES)
			infile->name = tmp->h_name;///!\ au double free si infile->heredoc == YES (comme on free heredoc et infile)
		tmp = tmp->next;
		nb_lim--;
		i++;
	}
}

static void	ft_fill_heredoc(t_lim *heredoc, int fd, int fd_pipe[2])//dans les child, voir set_heredoc
{
	char	*line;
	char	*lim;

//fd_pipe pour les signaux & gestion d'erreur
	(void)fd_pipe;//A Supprimer une fois implemente !!!!!!!!! (pouet)
	lim = heredoc->limit;
	line = readline("> ");
	if (heredoc->quotes == YES)
	{
		while (line && ft_strncmp(line, lim, ft_strlen(lim) + 1))
		{
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
	else
	{
		while (line && ft_strncmp(line, lim, ft_strlen(lim) + 1))
		{
			// expand => soit c'est une var, soit une ligne de cmd => parcourir la ligne, tokeniser /!\redirections à voir
			ft_putstr_fd(line, fd);//a suppr quand expand ok
			ft_putstr_fd("\n", fd);//a suppr quand expand ok
			free(line);
			line = readline("> ");
			if (!line)//A checker : ctrl D n'est a gerer que pour exit du shell normalement => vérifier comment les signaux réagissent ici
				ft_putstr_fd("Avertissement car EOF et pas limiter (ferme avec ctrl+D et pas mot-clef), mais la suite s'exécute bien.\n", 1);//a reformuler
		}
		if (line)
			free(line);
	}
}

int	ft_set_heredoc(int nb_lim, t_lim *heredoc, t_fdata *infile, int fd_pipe[2])//a faire dans les child
{
	t_lim	*tmp;
	int		fd;
//OUVERTS : Infile (fdp-1[0], si exc != exc->head), fdp[0]*, fdp[1]* (*si one->next != NULL)
	tmp = heredoc;
	while (nb_lim)
	{
		fd = open(tmp->h_name, O_WRONLY | O_TRUNC | O_CREAT, 0664);//creer le fichier pour que les suivants ne le tentent pas
		if (fd == -1)
		{
			ft_putstr_fd("Open here_doc file is impossible.\n", 2);
			return (-1);//ERROR
		}
		else
			ft_fill_heredoc(tmp, fd, fd_pipe);
		nb_lim--;
		if (close(fd) == -1)//On a open pour write donc on close quoi qu'il arrive, on rouvrira en lecture apres 
			return (-1);//ERROR
		if (nb_lim || infile->heredoc != YES)
		{
			if (unlink(tmp->h_name) == -1)//Faudra unlink infile->name si infile->heredoc == YES quand j'aurai fini de l'utiliser
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}
