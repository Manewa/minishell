/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:17:31 by namalier          #+#    #+#             */
/*   Updated: 2025/02/14 13:58:17 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	error_write(t_token *current, t_exec *exec)
{
	exec->files->outfile->opening_failure = PERMISSION_DENIED;
	while (current->next && current->next->type != PIPE)
	{
		current = current->next;
		if (current && current->type == HEREDOC)
			exec_heredoc(current, exec);
	}
	return ;
}

void exec_append(t_token *current, t_exec *exec)
{
	int	fd;

	if (exec->files->outfile->opening_failure == PERMISSION_DENIED)
		return ;
	exec->files->outfile->name = ft_strdup(current->line_wip);
	if (access(current->line_wip, F_OK) == 0)
	{
		if (access(current->line_wip, W_OK) != 0)
			return (error_write(current, exec));
	}
	fd = open(exec->files->outfile->name, O_RDONLY | O_CREAT, 0664);
	if (fd == -1)
		exec->files->outfile->opening_failure = 1;
	else
	{
		exec->files->outfile->opening_failure = 0;
		close (fd);
	}
}
