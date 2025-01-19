/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:55:57 by namalier          #+#    #+#             */
/*   Updated: 2025/01/14 15:52:38 by natgomali        ###   ########.fr       */
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
	if (c == '>')
		return ('>');
	if (c == '<')
		return ('<');
	if (c == '|')
		return ('|');
	else
		return (0);
}

char *strdup_end(char *line, int *readed, int start)
{
	int		i;
	size_t	j;
	char	*str;

	i = start;
	j = 0;
	str = malloc((*readed - start + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < *readed)
		str[j++] = line[i++];
	str[j] = '\0';
	return (str);
}
