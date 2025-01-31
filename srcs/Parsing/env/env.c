/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:10:04 by namalier          #+#    #+#             */
/*   Updated: 2025/01/31 16:12:22 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void ft_cpypath(t_infos *infos, t_exec *exec)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!infos->env)
		return ;
	while (infos->env[i] && ft_strnstr(infos->env[i], "PATH=", 5) == 0)
		i++;
	if (!infos->env[i])
	{
		infos->path = NULL;
		return ;
	}
	str = ft_strdup(&(infos->env[i][5]));
	if (!str)
		return ;
	exec->path = ft_split(str, ':');
	free (str);
	if (!(infos->path))
		return ;
}

/* cpyenv is copying char **envp to infos->env adding NULL in last char * */

int	ft_cpyenv(t_infos *infos, char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
		i++;
	infos->env = malloc((i + 1) * sizeof(char *));
	if (!infos->env)
		return (0);
	i = 0;
	while (envp[i])
	{
		infos->env[i] = ft_strdup(envp[i]);
		if (!infos->env[i])
			return (0);
		i++;
	}
	infos->env[i] = NULL;
	return (1);
}

int cpy_env_from_infos(t_infos *infos, t_exec *exec)
{
	size_t	i;

	i = 0;
	while (infos->env[i])
		i++;
	exec->env = malloc((i + 1)*sizeof(char*));
	i = 0;
	while (infos->env[i])
	{
		exec->env[i] = ft_strdup(infos->env[i]);
		if (!exec->env[i])
			return (0);
		i++;
	}
	exec->env[i] = NULL;
	return (1);
}
