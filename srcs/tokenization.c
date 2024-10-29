/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:59:53 by namalier          #+#    #+#             */
/*   Updated: 2024/10/29 17:53:19 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*token_type(t_infos *infos, size_t *i)
{
	t_token	*token;

	if (!ft_lstnew(&token))
		return (token);
//	if (infos->line[*i] == ' ')
//		token_spaces(infos, i, token);
	if (infos->line[*i] == 34)
		token_doublequote(infos, i, token);
/*	else if (infos->line[*i] == 39)
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
		token_word(infos, i, token);*/
	return (token);
}

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
}
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
