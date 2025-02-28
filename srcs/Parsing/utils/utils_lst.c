/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:50:57 by namalier          #+#    #+#             */
/*   Updated: 2025/02/20 15:55:16 by natgomali        ###   ########.fr       */
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

t_exec *ft_execnew(t_exec *head, t_infos *infos)
{
	t_exec	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	if (head != NULL)
		new->head = head;
	if (infos)
		new->infos = infos;
	new->limiter = NULL;
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
	infile->name = 0;
	outfile = malloc(sizeof(*outfile));
	if (!outfile)
		return (NULL);
	outfile->name = 0;
	new->infile = infile;
	new->outfile = outfile;
	new->infile->heredoc = NO_INFO;
	new->infile->opening_failure = 0;
	new->outfile->opening_failure = 0;
	return (new);
}
