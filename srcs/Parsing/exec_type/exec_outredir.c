# include "../../../includes/minishell.h"

void exec_outredir(t_token *current, t_exec *exec)
{
	int	fd;   

	exec->files->outfile->name = ft_strdup(current->line_wip);
	fd = open(exec->files->outfile->name, O_RDONLY | O_CREAT, 0664);
	if (fd == -1)
		exec->files->opening_failure = 1;
	else
	{
		exec->files->opening_failure = 0;
		close (fd);
	}
}

