# include "../../../includes/minishell.h"

void exec_inredir(t_token *current, t_exec *exec)
{
	size_t	i;
	int		fd;

	i = 0;
	while (current->line_wip[i])
	{
		exec->files->infile->name[i] = current->line_wip[i];
		i++;
	}
	fd = open(exec->files->infile->name, O_RDONLY);
	if (fd == -1)
		exec->files->opening_failure = 1;
	else
	{
		exec->files->opening_failure = 0;
		close(fd);
	}
}
