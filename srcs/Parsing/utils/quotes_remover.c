/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remover.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:49:18 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/29 01:16:58 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	quotes_count(char *str)
{
	int		quotes;
	size_t	i;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == 39)
			quotes += 1;
		i++;
	}
	return (quotes);
}

static char	*quotes_remover(char *str, int *first, int second)
{
	int		i;
	int		j;
	char	*new_line;

	new_line = malloc((ft_strlen(str) - 1) * sizeof(char));
	if (!new_line)
		return (NULL);
	i = 0;
	j = 0;
	while (i < *first)
		new_line[j++] = str[i++];
	(*first)++;
	while (*first < second)
		new_line[j++] = str[(*first)++];
	while (str[++second])
	{
		new_line[j++] = str[second];
	}
	new_line[j] = '\0';
	*first -= 1;
	free(str);
	return (new_line);
}

void	quotes_detecter(t_exec *current)
{
	int	i;
	int	first;
	int	second;

	i = 0;
	while (current && current->cmd_array && current->cmd_array[i])
	{
		first = 0;
		while (current->cmd_array[i][first])
		{
			if (current->cmd_array[i][first] == '"')
			{
				second = first;
				out_of_dquote(current->cmd_array[i], &second);
				current->cmd_array[i] = quotes_remover(current->cmd_array[i],
						&first, second);
			}
			else if (current->cmd_array[i][first] == 39)
			{
				second = first;
				out_of_squote(current->cmd_array[i], &second);
				current->cmd_array[i] = quotes_remover(current->cmd_array[i],
						&first, second);
			}
			else
				first++;
		}
		i++;
	}
}

void	quotes_detecter_heredoc(t_lim *head)
{
	int		first;
	int		second;
	t_lim	*current;

	current = head;
	while (current && current->limit)
	{
		first = 0;
		while (current->limit[first])
		{
			if (current->limit[first] == '"')
			{
				second = first;
				out_of_dquote(current->limit, &second);
				current->limit = quotes_remover(current->limit,
						&first, second);
			}
			else if (current->limit[first] == 39)
			{
				second = first;
				out_of_squote(current->limit, &second);
				current->limit = quotes_remover(current->limit,
						&first, second);
			}
			else
				first++;
		}
		current = current->next;
	}
}
