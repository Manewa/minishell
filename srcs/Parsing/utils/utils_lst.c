/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:50:57 by namalier          #+#    #+#             */
/*   Updated: 2024/12/04 16:57:38 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_token	*ft_tokenlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	ft_tokenlast(tmp)->next = new;
}

t_token	*ft_tokennew(t_token *prev)
{
	t_token	*new;

	new = malloc(sizeof(new));
	if (!new)
		return (NULL);
	if (prev != NULL)
		new->prev = prev;
	new->next = NULL;
	return (new);
}
