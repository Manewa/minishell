/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:01:20 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/29 00:41:02 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	redirection_error(char *line, size_t *i)
{
	(*i)++;
	if (line [*i] && line[*i] == line[*i - 1])
		(*i)++;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (line[*i -1] == '<' && line[*i] == '>')
		return (++(*i));
	else if (line[*i] == '<' || line[*i] == '>' || line [*i] == '|')
		return (*i);
	if (!line[*i])
		return (*i);
	return (0);
}

int	pipe_error(char *line, size_t i)
{
	i++;
	while (line [i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '|')
		return (DOUBLE_PIPE);
	return (0);
}

int	check_error_parsing(t_infos *infos)
{
	size_t	i;

	i = 0;
	while (infos && infos->line && (infos->line[i] == ' '
			|| infos->line[i] == '\t'))
		i++;
	if (infos && infos->line && infos->line[i] == '|')
		return (PIPE);
	i = 0;
	while (infos->line && infos->line[i])
	{
		if (infos->line[i] == '|')
		{
			if (pipe_error(infos->line, i))
				return (DOUBLE_PIPE);
		}
		if (infos->line[i] == '<' || infos->line[i] == '>')
		{
			if (redirection_error(infos->line, &i) != 0)
				return (i);
		}
		i++;
	}
	return (0);
}

int	check_error(t_infos *infos)
{
	int	error;

	error = check_error_parsing(infos);
	if (error == PIPE)
	{
		ft_error_parsing(infos, 0, '|');
		return (1);
	}
	else if (error == DOUBLE_PIPE)
	{
		infos->exit_val = 2;
		ft_free_infos(infos,
			"minipouet : syntax error near unexpected token `|'\n", 0);
		return (1);
	}
	else if (error != 0)
	{
		ft_error_parsing(infos, 0, infos->line[error]);
		return (1);
	}
	else
		return (0);
}

/*int	check_error_parsing(t_infos *infos)
{
	size_t	i;
	size_t	j;
	char	c;

	i = 0;
	j = 0;
	while (infos->line[i])
	{
		if (is_separator(infos->line[i]))
		{
			c = is_separator(infos->line[i]);
			j = i;
			while (infos->line[i] == c)
				i++;
			if (i - j > 2)
				return (ft_error_parsing(infos, 0, infos->line[j + 2]));
			while (infos->line[i] == ' ' || infos->line[i] == '''
					|| infos->line[i] == '"')
			{
				if (infos->line[i] == ''')
				{
					while (infos->line[i] == ' ' && infos->line[i] == ''')
						i++;
				}
				else if (infos->line[i] == '"')
				{
					while (infos->line[i] == ' ' && infos->line[i] == '"')
						i++;
				}
				i++;
			}
			if (is_separator(infos->line[i]))
				return (ft_error_parsing(infos, 0, infos->line[i]));
		}
		
		i++;
	}
}*/
