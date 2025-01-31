# include "../../../includes/minishell.h"

void exec_heredoc(t_token *current, t_exec *exec)
{
	exec->is_heredoc = OUI;
	exec->delimiter = ft_strdup(current->line_wip);
//	exec->files->infile->name = "heredoc";
}
