/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:17:46 by namalier          #+#    #+#             */
/*   Updated: 2025/03/04 18:23:01 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* initialise limiter struct
 */

t_lim *limiter_init(t_token *token, t_exec *exec)
{
	t_lim *lim;

	lim = ft_limnew();
	if (exec->limiter)
		(ft_limlast(exec->limiter))->next = lim;
	lim->next = NULL;
	if (token->quotes == 0)
		lim->quotes = NO;
	else
		lim->quotes = YES;
	lim->limit = ft_strdup(token->line_wip);
	if (!lim->limit)
		return (NULL);
	return (lim);
}

/*
 * if heredoc, store 1 in exec->is_heredoc
 * init a list called lim to store every heredoc limiter
 * Use an int YES in exec->files->heredoc
 */

void exec_heredoc(t_token *current, t_exec *exec)
{
	t_lim	*lim;

	exec->is_heredoc += 1;
	lim = limiter_init(current, exec);
	ft_limadd_back(&(exec->limiter), lim);
	if (exec->files->infile->heredoc == NO_INFO)
		exec->files->infile->heredoc = YES;
}
