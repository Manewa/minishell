# include "../../../includes/minishell.h"

void error_read(t_token *current, t_exec *exec)
{
	exec->files->infile->opening_failure = PERMISSION_DENIED;
	while (current->next && current->next->type != PIPE)
	{
		current = current->next;
		if (current && current->type == HEREDOC)
			exec_heredoc(current, token);
	}
	return ;
}

void exec_inredir(t_token *current, t_exec *exec)
{
	int	fd;

	exec->files->infile->name = ft_strdup(current->line_wip);
	exec->files->infile->heredoc = NO;
	if (access(current->line_wip, F_OK))
	{
		if (!access(current->line_wip, R_OK))
			return (error_read(current, token));
		else
			exec->files->infile->opening_failure = FILE_DOES_NOT_EXIST;
	}
}
