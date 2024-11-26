/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:55:57 by namalier          #+#    #+#             */
/*   Updated: 2024/11/26 16:25:24 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_special_char(t_infos *infos, size_t *i)
{
	if (infos->line[*i] == 34 || infos->line[*i] == 39 || infos->line[*i] == '<'
			|| infos->line[*i] == '>' || infos->line[*i] == '|'
			|| infos->line[*i] == ' ')
		return (1);
	return (0);
}

char	is_separator(char c)
{
	if (c == ' ')
		return (' ');
	if (c == '>')
		return ('>');
	if (c == '<')
		return ('<');
	if (c == '|')
		return ('|');
	else
		return (false);
}


