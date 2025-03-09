/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:59:53 by namalier          #+#    #+#             */
/*   Updated: 2025/03/08 18:54:34 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* line -> Toute la line envoye au prompt
 * readed -> ce qui a ete lu. Envoye en pointeur pour mettre a jour l'avancement dans la line
 * start -> point de depart avant de trouver le type du nouveau token
 * sep -> Le char qui a defini un nouveau token
 Cette fonction permet de trouver le type du token, sans prendre en compte les quotes*/

int	token_type(char *line, int readed, int start, char sep)
{
	while (line[readed] && line[readed] == line[start])
		readed++;
	if (sep == 0)
		return (WORD);
	else if (sep == '>')
	{
		if (readed - start == 2)
			return (APPEND_MODE);
		else if (readed - start == 1)
			return (OUTREDIR);
	}
	else if (sep == '<')
	{
		if (readed - start == 2)
			return (HEREDOC);
		else if (readed - start == 1)
			return (INREDIR);
	}
	else if (sep == '|' && readed - start == 1)
		return (PIPE);
	return  (ERROR_PARSING);
}

/* Permet d'initialiser un nouveau token avec la tete si jamais ce ne l'est pas deja)*/

t_token *init_token(t_infos *infos, t_token *head)
{
	t_token	*token;

	token = ft_tokennew(head);
	if (!token)
		return (ft_free_infoken(infos, head, "ERROR : malloc token", 0));
	token->type = 0;
	token->infos = infos;
	token->type = 0;
	token->quotes = 0;
	return (token);
}

/* Permet de creer, pour l'instant, le premier token*/

t_token	*create_token(t_infos *infos, int *readed, int *start)
{
	t_token	*token;

	token = init_token(infos, 0);
	if (!token)
		return (NULL);
	token->type = token_type(infos->line, *readed, *start,
			is_separator(infos->line[*readed]));
	if	(token->type == ERROR_PARSING)
		return (ft_error_parsing(infos, token, infos->line[*readed]));
	else if (token->type == PIPE)
		return (token);
	token_line_wip(token, infos->line, readed, start);
	if (!token->line_wip)
		return (NULL);
	return(token);
}

t_token	*tokenization(t_infos *infos)
{
	t_token	*token_head;
	t_token	*token_new;
	int		readed;
	int		start;

	readed = 0;
	start = 0;
	infos->line = expand_main(infos->line, infos);
	token_head = create_token(infos, &readed, &start);
	if (!token_head)
		return(0);
	while (infos->line[readed])
	{
		start = readed;
		token_new = init_token(infos, token_head);
		if (!token_new)
			return (NULL);
		token_new->prev = ft_tokenlast(token_head);
		ft_tokenadd_back(&token_head, token_new);
		token_new->type = token_type(infos->line, readed, start,
				is_separator(infos->line[readed]));
		if	(token_new->type == ERROR_PARSING)
			return (ft_error_parsing(infos, token_head, infos->line[readed]));
		else if (token_new->type != PIPE)
		{
			token_line_wip(token_new, infos->line, &readed, &start);
			if (!(token_new->line_wip))
					return (ft_free_infoken(infos, token_head, "malloc\n", 0));
			while (infos->line[readed] && infos->line[readed] == ' ')
				readed++;
		}
		else if (token_new && token_new->prev && token_new->prev->type == PIPE)
			return (ft_free_infoken(infos, token_head, "psh : double pipe", 0));
		else if (token_new->type == PIPE)
			while (infos->line[++readed] && infos->line[readed] == ' ');
		else if (infos->line[readed])
			readed++;
	}
	return (token_head);
}
