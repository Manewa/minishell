/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:18:10 by namalier          #+#    #+#             */
/*   Updated: 2025/02/18 12:44:48 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
/**
 * exec word ne fonctionne pas avec un truc du style ls -l << Pouet -a. A changer*/
void exec_word(t_token *current, t_exec *exec)
{
	if (exec->cmd_array)
		return ;
	exec->cmd_array = malloc(exec_count_word(current) * sizeof(char*));
	fill_cmd_array(exec, current);
	if (!exec->cmd_array)
		return ;
	find_pathcmd(exec->path, exec);
}

