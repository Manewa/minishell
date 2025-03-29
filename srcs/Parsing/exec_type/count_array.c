/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:00:14 by namalier          #+#    #+#             */
/*   Updated: 2025/03/29 00:36:14 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_count_word_exec(char *s, char c)
{
	int	count_word;
	int	i;

	i = 0;
	count_word = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count_word++;
			while (s[i] && s[i] != c)
			{
				if (s[i] == 39)
					out_of_squote(s, &i);
				else if (s[i] == '"')
					out_of_dquote(s, &i);
				i++;
			}
		}
		if (s[i])
			i++;
	}
	return (count_word);
}

char	*fill_word(t_token *token, int *i)
{
	int		j;
	int		k;
	char	*str;

	k = 0;
	while (token->line_wip[*i] && token->line_wip[*i] == ' ')
		(*i)++;
	j = *i;
	while (token->line_wip[*i] && token->line_wip[*i] != ' ')
	{
		if (token->line_wip[*i] == '"' || token->line_wip[*i] == 39)
		{
			out_of_quotes(token->line_wip, i);
			if (j == *i - 1)
				j = *i + 1;
		}
		(*i)++;
	}
	str = malloc((*i - j + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (j < *i)
		str[k++] = token->line_wip[j++];
	str[k] = '\0';
	return (str);
}

void	fill_cmd_array(t_exec *exec, t_token *token)
{
	int	i;
	int	k;

	k = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
		{
			i = 0;
			while (token->line_wip[i])
			{
				exec->cmd_array[k] = fill_word(token, &i);
				k++;
				if (token->line_wip[i])
					i++;
				while (token->line_wip[i] == ' ')
					i++;
			}
		}
		token = token->next;
	}
	exec->cmd_array[k] = NULL;
}

/*
 * Count the number of word in each token
 */

int	exec_count_word(t_token *token)
{
	t_token	*tmp;
	int		count;

	tmp = token;
	count = 1;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			count += ft_count_word_exec(tmp->line_wip, ' ');
		tmp = tmp->next;
	}
	return (count);
}
