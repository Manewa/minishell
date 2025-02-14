/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_inredir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:17:55 by namalier          #+#    #+#             */
/*   Updated: 2025/02/14 13:22:51 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void error_read(t_token *current, t_exec *exec)
{
	exec->files->infile->opening_failure = PERMISSION_DENIED;
	while (current->next && current->next->type != PIPE)
	{
		current = current->next;
		if (current && current->type == HEREDOC)
			exec_heredoc(current, exec);
	}
	return ;
}

void exec_inredir(t_token *current, t_exec *exec)
{
	exec->files->infile->name = ft_strdup(current->line_wip);
	exec->files->infile->heredoc = NO;
	if (access((current->line_wip), F_OK) == 0)
	{
		if (access((current->line_wip), R_OK) != 1)
			return (error_read(current, exec));
		else
			exec->files->infile->opening_failure = FILE_DOES_NOT_EXIST;
	}
}
