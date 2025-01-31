/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:55:57 by namalier          #+#    #+#             */
/*   Updated: 2025/01/20 14:47:04 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	out_of_heredoc(char *line, int *i)
{
	(*i)++;
	(*i)++;
	while (line[*i] && line[*i] == ' ')
	(*i)++;
	while (line[*i] && line[*i] != ' ' && is_separator(line[*i]) == 0)
	{
		if (line[*i] == 39)
			out_of_squote(line, i);
		else if (line[*i] == '"')
			out_of_dquote(line, i);
		else
			(*i)++;
	}

}

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
	else if (c == '<')
		return ('<');
	else if (c == '|')
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

