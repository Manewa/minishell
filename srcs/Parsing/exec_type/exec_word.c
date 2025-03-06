/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:18:10 by namalier          #+#    #+#             */
/*   Updated: 2025/03/04 18:35:19 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/minishell.h"

/*
 * Malloc the new path + cmd and put it in cmd_array[0]
 */

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

/*
 * try to find for each path a command that is stored in exec->cmd_array[0]
 */

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
 * main for exec_word
 */

void exec_word(t_token *current, t_exec *exec)
{
	if (exec->cmd_array)
		return ;
	exec->cmd_array = malloc(exec_count_word(current) * sizeof(char*));
	fill_cmd_array(exec, current);
	if (!exec->cmd_array)
		return ;
	exec->builtin = builtin_cmp(exec->cmd_array[0]);
	if (exec->builtin == 0)
		find_pathcmd(exec->path, exec);
}

