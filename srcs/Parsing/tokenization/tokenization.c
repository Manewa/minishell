/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:59:53 by namalier          #+#    #+#             */
/*   Updated: 2025/01/16 18:16:50 by natgomali        ###   ########.fr       */
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
	while (line[readed] && line[readed] == sep)
	{
			readed++;
		if (sep == ' ' && line[readed])
			sep = is_separator(line[readed]);
	}
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
	else if (sep == '|')
		return (PIPE);
	return  (ERROR_PARSING);
}

/* Permet d'initialiser un nouveau token avec la tete si jamais ce ne l'est pas deja)*/

t_token *init_token(t_infos *infos, t_token *head)
{
	t_token	*token;

	token = ft_tokennew(head);
	if (token == NULL)
		return (token);
	token->type = 0;
	token->infos = &infos;
	ft_cpypath(infos);
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
	while (infos->line[readed])
	{
		start = readed;
		token_new = init_token(infos, token_head);
		if (!token_new)
			return (NULL);
		token_new->type = token_type(infos->line, readed, start,
				is_separator(infos->line[readed]));
		token_line_wip(token_new, infos->line, &readed, &start);
		ft_tokenadd_back(&token_head, token_new);
	}
	return (token_head);
}

/*
   t_token	*token_type(t_infos *infos, size_t *i)
   {
   t_token	*token;

   if (!ft_lstnew(&token))
   return (token);
//	if (infos->line[*i] == ' ')
//		token_spaces(infos, i, token);
if (infos->line[*i] == 34)
token_doublequote(infos, i, token);
else if (infos->line[*i] == 39)
token_singlequote(infos, i, token);
else if (infos->line[*i] == '<')
{
if (infos->line[*i + 1] == '<')
token_heredoc(infos, i, token);
token_inredir(infos, i, token);
}
else if (infos->line[*i] == '>')
{
if (infos->line[*i + 1] == '>')
token_append(infos, i, token);
token_outredir(infos, i, token);
}
else if (infos->line[*i] == '|')
token_pipe(infos, i, token);
else
token_word(infos, i, token);
return (token);
}
*/
/*
   t_token	*tokenization(t_infos *infos)
   {
   t_token	*lst_token;
   t_token	*tmp_token;
   t_token	*prev_token;
   size_t	i;

   i = 0;
   lst_token = token_type(infos, &i);
   lst_token->prev = NULL;
   if (!lst_token)
   return (lst_token);
   while (infos->line[i])
   {
   if (!prev_token)
   prev_token = lst_token;
   else
   prev_token = tmp_token;
   tmp_token = token_type(infos, &i);
   ft_tokenadd_back(&lst_token, tmp_token);
   tmp_token->head = lst_token;
   tmp_token->prev = prev_token;
   }
//	tokens_for_exec(&lst_token, infos);
return (lst_token);
}*/
/*
   type = token_type(infos, &i);
   if (type == SPACES)
   token_space(infos, &token, &i);
   else if (type == DOUBLE_QUOTE)
   token_doublequote(infos, &token, &i);
   else if (type == SINGLE_QUOTE)
   token_singlequote(infos, &token, &i);
   else if (type == HEREDOC)
   token_heredoc(infos, &token, &i);
   else if (token_type(infos, i) == OUTREDIR)
   token_outredir(infos, &token, &i);
   else if (type == INREDIR)
   token_inredir(infos, &token, &i);
   else if (type == APPEND_MODE)
   token_append_mode(infos, &token, &i);
   else if (type == PIPE)
   token_pipe(infos, &token);
   else
   token_word(infos, &i, &token);
   i++;
   }
   return (token);
   }*/

