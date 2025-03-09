/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:47:11 by namalier          #+#    #+#             */
/*   Updated: 2025/03/08 18:58:57 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* Copy the token in line_wip
 */

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

/* Return if there is quotes in the heredoc limiter or not
 * Fill the token heredoc with the line in line_wip
 * pass every << and space at the beggining of the line
 */

int	line_heredoc(char *line, int *start, int *readed, t_token *token)
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
	return (count_quote);
}

/* token_line a pour but de remplir la line_wip dans token, et donc de connaitre
 * le debut du token et ou il s'arrete
 * Permet aussi de verifier que les quotes sont bien fermees, sinon change le type de la node a QUOTE_NOT_CLOSED*/

void	token_line_wip(t_token *token, char *line, int *readed, int *start)
{
	int		count_quote;

	count_quote = 0;
	if (token->type == HEREDOC)
	{
		token->quotes = line_heredoc(line, start, readed, token);
		return ;
	}
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
	if (token->type == QUOTE_NOT_CLOSED)
	{
		ft_putstr_fd("pouetsh : error quote not closed", 2);
		ft_free_infoken(token->infos, token, 0, 0);
		return ;
	}
	ft_cpytoken(token, line, *start, *readed);
	*start = *readed;
}
