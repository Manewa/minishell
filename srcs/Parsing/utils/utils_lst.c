/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:50:57 by namalier          #+#    #+#             */
/*   Updated: 2025/03/09 10:20:38 by natgomali        ###   ########.fr       */
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

	new = malloc(sizeof(t_exec));
	if (!new)
		return (NULL);
	if (head != NULL)
		new->head = head;
	if (infos)
		new->infos = infos;
	new->limiter = NULL;
	new->next = NULL;
	new->is_heredoc = 0;
	new->builtin = 0;
	new->cmd_array = 0;
	new->env = 0;
	new->path = 0;
	new->cmd_path = 0;
	return (new);
}

t_token	*ft_tokennew(t_token *prev)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	if (prev != NULL)
		new->prev = prev;
	new->next = NULL;
	new->line_wip = 0;
	return (new);
}

t_files	*ft_filenew(void)
{
	t_files	*new;
	t_fdata	*infile;
	t_fdata	*outfile;

	new = malloc(sizeof(t_files));
	if (!new)
		return (NULL);
	infile = malloc(sizeof(t_fdata));
	if (!infile)
		return (NULL);
	infile->name = 0;
	outfile = malloc(sizeof(t_fdata));
	if (!outfile)
		return (NULL);
	outfile->name = 0;
	new->infile = infile;
	new->outfile = outfile;
	new->infile->fd = -1;
	new->outfile->fd = -1;
	new->infile->heredoc = NO_INFO;
	new->outfile->heredoc = NO_INFO;
	new->infile->opening_failure = 0;
	new->outfile->opening_failure = 0;
	return (new);
}
