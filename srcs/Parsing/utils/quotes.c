/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:30:55 by namalier          #+#    #+#             */
/*   Updated: 2025/01/24 13:36:54 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* Out of dquote for double quote 
 * out of squote for single quote
 * Both move the index to the char right after the second quote*/

int	out_of_dquote(char *line, int *readed)
{
	int	count_quote;

	if (line[*readed])
		(*readed)++;
	count_quote = 1;
	while (line[*readed] && count_quote == 1)
	{
		if (line[*readed] && line[*readed] == '"')
			count_quote += 1;
		else
			(*readed)++;
	}
	return(count_quote);
}

int	out_of_squote(char *line, int *readed)
{
	int	count_quote;

	if (line[*readed])
		(*readed)++;
	count_quote = 1;
	while (line[*readed] && count_quote == 1)
	{
		if (line[*readed] == 39)
			count_quote += 1;
		else
			(*readed)++;
	}
	return(count_quote);
}

/*int	new_doublequote(t_infos	*infos, size_t *i, size_t *count_flags,
						size_t count_quote)
{
	while (infos->line[*i] && (infos->line[*i++] == 34 || ))
	{
		*count_quote += 1;
		while (infos->line[*i] && infos->line[*i] != 34)
			i++;
		if (infos->line[*i] && infos->line[*i - 1] == 34)
			i++;
		else if (!infos->line[*i])
			return (1);
		while (infos->line[*i] && (infos->line[*i] != ' '
					|| !is_special_char(infos->line[*i])))
			i++;
		if (infos->line[*i] 
	}
	return (0);
}

void	token_doublequote(t_infos *infos, size_t *i, t_token *token)
{
	size_t	j;
	size_t	count_flags;
	int		count_quote;

	count_quote = 1;
	j = ++(*i);
	while (infos->line[*i] && infos->line[*i] != 34)
		*i += 1;
	count_flags = 1;
	if (infos->line[*i] && (infos->line[*i] == 34
		|| !is_special_char(infos, i)))
		{
			while (infos->line[*i] && (infos->line[*i++] == 34))
			{
				while (infos->line[*i] && infos->line[*i] != 34)
					i++;
				if (infos->line[*i])
					i++;
			}
			while (infos->line[*i] && 
		}
*/	
/*	while (infos->line[*i] && (infos->line[*i] == 34 || !is_special_char(infos, i)))
	{
		*i += 1;
		if (is_special_char(infos, i) && infos->line[*i] != 34)
			break ;
		while (infos->line[*i] && infos->line[*i] != 34)
			*i += 1;
		if (infos->line[*i] == 34)
			count_quote += 1;
	}
	if (!infos->line[*i])
		token->type = ERROR_PARSING;
	token->word = malloc((*i - j - count_quote + 1) * sizeof(char));

	
}*/
