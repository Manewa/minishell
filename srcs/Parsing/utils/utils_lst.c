/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:50:57 by namalier          #+#    #+#             */
/*   Updated: 2025/01/24 14:16:31 by namalier         ###   ########.fr       */
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

t_exec *ft_execnew(t_exec *prev)
{
	t_exec	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	if (prev != NULL)
		new->prev = prev;
	new->next = NULL;
	return (new);
}

t_token	*ft_tokennew(t_token *prev)
{
	t_token	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	if (prev != NULL)
		new->prev = prev;
	new->next = NULL;
	return (new);
}

t_files	*ft_filenew(void)
{
	t_files	*new;
	t_fdata	*infile;
	t_fdata	*outfile;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	infile = malloc(sizeof(*infile));
	if (!infile)
		return (NULL);
	outfile = malloc(sizeof(*outfile));
	if (!outfile)
		return (NULL);
	new->infile_info = infile;
	new->outfile_info = outfile;
	new->opening_failure = 0;
	return (new);
}
