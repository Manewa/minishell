/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorted_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 00:05:30 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/29 00:05:38 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	len_env_line(t_env *tmp)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(tmp->key);
	j = ft_strlen(tmp->value);
	return (i + j + 2);
}

t_env	*insert_sorted(t_env *head, t_env *new)
{
	t_env	*current;

	current = head;
	if (!head || ft_strcmp(new->key, head->key) < 0)
	{
		new->next = head;
		return (new);
	}
	while (current->next && ft_strcmp(current->next->key, new->key) < 0)
		current = current->next;
	new->next = current->next;
	current->next = new;
	return (head);
}

void	sort_env_list(t_env **head)
{
	t_env	*current;
	t_env	*sorted;
	t_env	*next;

	sorted = NULL;
	current = *head;
	while (current)
	{
		next = current->next;
		sorted = insert_sorted(sorted, current);
		current = next;
	}
	*head = sorted;
}
