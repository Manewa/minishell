/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:30:55 by namalier          #+#    #+#             */
/*   Updated: 2025/03/29 01:14:45 by natgomali        ###   ########.fr       */
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
	return (count_quote);
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
	return (count_quote);
}

int	check_quotes(char *str)
{
	int	i;
	int	count_quotes;

	i = 0;
	while (str[i])
	{
		count_quotes = 0;
		while (str[i] && str[i] != '|')
		{
			if (str[i] == '"')
				count_quotes += out_of_dquote(str, &i);
			else if (str[i] == 39)
				count_quotes += out_of_squote(str, &i);
			if (str[i])
				i++;
		}
		while (str[i] && str[i] == '|')
			i++;
	}
	if (count_quotes % 2 != 0)
	{
		ft_putstr_fd("minipouet : error quote not closed\n", 2);
		return (0);
	}
	return (1);
}

int	out_of_quotes(char *str, int *i)
{
	int	count_quotes;

	count_quotes = 0;
	if (str[*i] == 39)
		count_quotes = out_of_squote(str, i);
	else if (str[*i] == '"')
		count_quotes = out_of_dquote(str, i);
	return (count_quotes);
}
