/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:47:11 by namalier          #+#    #+#             */
/*   Updated: 2025/01/30 15:58:42 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void ft_cpytoken(t_token *token, char *line,  int start, int readed)
{
	size_t	i;

	i = 0;
	while (line[start] == ' ')
		start++;
	token->line_wip = malloc((readed - start + 1)*sizeof(char));
	if (!token->line_wip)
		return ;
	while (start < readed)
		token->line_wip[i++] = line[start++];
	token->line_wip[i] = '\0';
}

void	line_heredoc(char *line, int *start, int *readed, t_token *token)
{
	int	count_quote;

	count_quote = 0;
	while (line[*readed] == '<')
		(*readed)++;
	while (line[*readed] == ' ')
		(*readed)++;
	*start = *readed;
	while (line[*readed] && is_separator(line[*readed]) == 0
			&& count_quote % 2 == 0 && line[*readed] != ' ')
	{
		if (line[*readed] == '"')
			count_quote += out_of_dquote(line, readed);
		if (line[*readed] == 39)
			count_quote += out_of_squote(line, readed);
		if (line[*readed])
			(*readed)++;
	}
	if (count_quote % 2 != 0)
		token->type = QUOTE_NOT_CLOSED;
	ft_cpytoken(token, line, *start, *readed);
	while (line[*readed] && line[*readed] && line[*readed] == ' ')
		(*readed)++;
	*start = *readed;	
}

/* token_line a pour but de remplir la line_wip dans token, et donc de connaitre
 * le debut du token et ou il s'arrete
 * Permet aussi de verifier que les quotes sont bien fermees, sinon change le type de la node*/

void	token_line_wip(t_token *token, char *line, int *readed, int *start)
{
	int		count_quote;

	count_quote = 0;
	if (token->type == HEREDOC)
		return (line_heredoc(line, start, readed, token));
//	else if (token->type == WORD)	
	while (line[*readed] && line[*readed] == ' ')
		(*readed)++;
	while (line[*readed] && is_separator(line[*readed]) != 0)
		(*readed)++;
	while (line[*readed] && line[*readed] == ' ')
		(*readed)++;
	*start = *readed;
	while (line[*readed] && is_separator(line[*readed]) == 0
			&& count_quote % 2 == 0)
	{
		if (line[*readed] == '"')
			count_quote += out_of_dquote(line, readed);
		if (line[*readed] == 39)
			count_quote += out_of_squote(line, readed);
		if (line[*readed] && line[*readed] == ' ' && token->type != WORD)
			break;
		if (line[*readed])
			(*readed)++;
	}
	if (count_quote % 2 != 0)
		token->type = QUOTE_NOT_CLOSED;
	ft_cpytoken(token, line, *start, *readed);
	*start = *readed;
}
