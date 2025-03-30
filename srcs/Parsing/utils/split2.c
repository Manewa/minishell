/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 12:37:01 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/30 12:37:25 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_first_quote(char *s, int *i, int *double_quote)
{
	while (s[*i] && (s[*i] == ' ' || s[*i] == '\t'))
		(*i)++;
	if (!s[*i])
		return (1);
	if (s[*i] == '"' && *double_quote == 1)
		*double_quote = 0;
	else if (s[*i] == '"' && *double_quote == 0)
		*double_quote = 1;
	return (0);
}

int	count_word_n_quotes(char *s, int *i, int *double_quote, int *start)
{
	int	count;

	count = 0;
	if (s[*i] == 39 && *double_quote == 0)
	{
		*start = *i;
		skip_quotes(s, i);
		if ((*i)++ > (*start) + 1)
			count++;
	}
	else
	{
		count++;
		while (s[*i] && !(s[*i] == ' ' || s[*i] == '\t'
				|| (s[*i] == 39 && *double_quote != 1)))
		{
			if (s[*i] == '"' && *double_quote == 1)
				*double_quote = 0;
			else if (s[*i] == '"' && *double_quote == 0)
				*double_quote = 1;
			(*i)++;
		}
	}
	return (count);
}
