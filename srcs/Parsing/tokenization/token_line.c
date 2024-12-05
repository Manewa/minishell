/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:47:11 by namalier          #+#    #+#             */
/*   Updated: 2024/12/05 17:36:09 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**parse_word(char *line, int *readed, int start, int count_quote)
{
	size_t	i;
	size_t	j;
	char	**tab;
	char	*part_of_line;

	i = 0;
	j = 0;
	part_of_line = strdup_end(line, readed, start);
	part_of_line = expander(part_of_line);
	tab = split_off_quote(part_of_line, ' ');
	while (tab[j])
	{

		j++;
	}
}

/* token_line a pour but de rendre une line prete a etre envoyee a l'exec dans un double tableau
 * permet aussi de verifier que les quote sont bien fermees, sinon change le type de la node*/

char	**token_line(t_token *token, char *line, int *readed, int start)
{
	char	**line_token;
	int		count_quote;

	start = *readed;
	count_quote = 0;
	while (line[*readed] && is_separator(line[*readed]) == 0
			&& count_quote % 2 == 0);
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
	if (token->type == WORD)
		line_token = parse_word(line, readed, start, count_quote);
	else if (token->type != ERROR_PARSING && token->type != QUOTE_NOT_CLOSED)
		line_token = parse_
}
