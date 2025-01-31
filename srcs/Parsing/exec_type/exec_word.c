# include "../../../includes/minishell.h"

char	*ft_pathcmd(char *argv, char *path)
{
	size_t	i;
	size_t	j;
	char	*cpath;

	i = 0;
	j = 0;
	if (!argv)
	{
		cpath = malloc(1*sizeof(char));
		cpath[0] = '\0';
		return (cpath);
	}
	cpath = malloc((ft_strlen(argv) + ft_strlen(path) + 2) * sizeof(char));
	if (!cpath)
		return (NULL);
	while (path[i])
	{
		cpath[i] = path[i];
		i++;
	}
	cpath[i++] = '/';
	while (argv[j])
		cpath[i++] = argv[j++];
	cpath[i] = '\0';
	return (cpath);
}

void	find_pathcmd(char **path, t_exec *exec)
{
	size_t	i;
	char	*pathcmd;

	i = 0;
	while (path[i])
	{
		pathcmd = ft_pathcmd(exec->cmd_array[0], exec->path[i]);
		if (!pathcmd)
			return ;
		if (access(pathcmd, F_OK | X_OK) == -1)
		{
			free(pathcmd);
			i++;
		}
		else
		{
			exec->cmd_array[0] = ft_strdup(pathcmd);
			free(pathcmd);
			return ;
		}
	}
}

void exec_word(t_token *current, t_exec *exec)
{
//	char	*path_tab;

	exec->cmd_array = split_off_quote(current->line_wip, ' ');
//	path_tab = ft_split(exec->path, ':');
	if (!exec->cmd_array)
		return ;
	find_pathcmd(exec->path, exec);
//	free (path_tab);

}

