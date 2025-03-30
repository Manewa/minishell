/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:47:11 by namalier          #+#    #+#             */
/*   Updated: 2025/03/29 18:52:00 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* Copy the token in line_wip
 */

void	ft_cpytoken(t_token *token, char *line, int start, int readed)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[start] == ' ' || line[start] == '\t')
		start++;
	token->line_wip = malloc((readed - start + 1) * sizeof(char));
	if (!token->line_wip)
		return ;
	while (start < readed)
	{
		if (line[start] == 39 || line[start] == '"')
		{	
			out_of_quotes(line, &j);
			while (++start < j)
				token->line_wip[i++] = line[start];
		}
		else
			token->line_wip[i++] = line[start++];
	}
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
	while (line[*readed] == ' ' || line[*readed] == '\t')
		(*readed)++;
	*start = *readed;
	while (line[*readed] && is_separator(line[*readed]) == 0
		&& count_quote % 2 == 0 && (line[*readed] != ' '
			|| line[*readed] == '\t'))
	{
		count_quote = out_of_quotes(line, readed);
		if (line[*readed])
			(*readed)++;
	}
	if (count_quote % 2 != 0)
		token->type = QUOTE_NOT_CLOSED;
	ft_cpytoken(token, line, *start, *readed);
	while (line[*readed] && line[*readed] && (line[*readed] == ' '
			|| line[*readed] == '\t'))
		(*readed)++;
	*start = *readed;
	return (count_quote);
}

static int	no_space_sep(char *line, int *start, int *readed, t_token *token)
{
	if (token->type == HEREDOC)
	{
		token->quotes = line_heredoc(line, start, readed, token);
		return (1);
	}
	while (line && line[*readed] && (line[*readed] == ' '
			|| line[*readed] == '\t'))
		(*readed)++;
	while (line && line[*readed] && is_separator(line[*readed]) != 0)
		(*readed)++;
	while (line && line[*readed] && (line[*readed] == ' '
			|| line[*readed] == '\t'))
		(*readed)++;
	return (0);
}

void	token_line_wip(t_token *token, char *line, int *readed, int *start)
{
	int		count_quote;

	count_quote = 0;
	if (no_space_sep(line, start, readed, token))
		return ;
	*start = *readed;
	while (line && line[*readed] && is_separator(line[*readed]) == 0
		&& count_quote % 2 == 0)
	{
		if (line && line[*readed] == '"')
			count_quote += out_of_dquote(line, readed);
		else if (line && line[*readed] == 39)
			count_quote += out_of_squote(line, readed);
		else if (line && line[*readed] && (line[*readed] == ' '
				|| line[*readed] == '\t') && token->type != WORD)
			break ;
		if (line && line[*readed])
			(*readed)++;
	}
	ft_cpytoken(token, line, *start, *readed);
	*start = *readed;
}
