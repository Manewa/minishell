/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:30:55 by namalier          #+#    #+#             */
/*   Updated: 2024/10/29 18:15:17 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	token_doublequote(t_infos *infos, size_t *i, t_token *token)
{
	size_t	j;
	int		count_quote;

	count_quote = 1;
	j = ++(*i);
	while (infos->line[*i] && infos->line[*i] != 34)
		*i += 1;
	while (infos->line[*i] && (infos->line[*i] == 34 || !is_special_char(infos, i)))
	{
		*i += 1;
		if (is_special_char(infos, i) && infos->line[*i] != 34)
			break ;
		while (infos->line[*i] && infos->line[*i] != 34)
			*i += 1;
		if (infos->line[*i] == 34)
			count_quote += 1;
	}
	token->word = malloc((*i - j - count_quote + 1) * sizeof(char));

}
