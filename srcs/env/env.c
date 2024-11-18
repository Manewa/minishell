/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:10:04 by namalier          #+#    #+#             */
/*   Updated: 2024/10/18 17:38:49 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
