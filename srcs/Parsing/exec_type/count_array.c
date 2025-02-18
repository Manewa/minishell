/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:00:14 by namalier          #+#    #+#             */
/*   Updated: 2025/02/18 12:52:20 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char *fill_word(t_token *token, int *i)
{
	int		j;
	int		k;
	char	*str;

	k = 0;
	while (token->line_wip[*i] && token->line_wip[*i] == ' ')
		i++;
	j = *i;
	while (token->line_wip[*i] && token->line_wip[*i] != ' ')
	{
		if (token->line_wip[*i] == 39)
			out_of_squote(token->line_wip, i);
		else if (token->line_wip[*i] == '"')
			out_of_dquote(token->line_wip, i);
		else
			(*i)++;
	}
	str = malloc((*i - j + 1)*sizeof(char));
	if (!str)
		return (NULL);
	while (j < *i)
		str[k++] = token->line_wip[j++];
	str[k] = '\0';
	return (str);
}

void fill_cmd_array(t_exec *exec, t_token *token)
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
			}
		}
		token = token->next;
	}
	exec->cmd_array[k] = NULL;
}

int exec_count_word(t_token *token)
{
	t_token *tmp;
	int		count;

	tmp = token;
	count = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			count += ft_count_word_quote(tmp->line_wip, ' ');
		tmp = tmp->next;
	}
	return (count);
}
