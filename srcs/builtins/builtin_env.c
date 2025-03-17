/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:57:36 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/17 14:15:57 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_safe_strlen(const char *c)
{
	size_t	i;

	if (!c)
		return (0);
	i = 0;
	while (c[i])
		i++;
	return (i);
}

void print_keynvalue(int fd, t_env *env)
{
	write(fd, env->key, ft_safe_strlen(env->key));
	write(fd, "=", 1);
	write(fd, env->value, ft_safe_strlen(env->value));
	write(fd, "\n", 1);
}

int	ft_env(t_infos *infos, t_exec *exec, t_fdata *outfile)
{
	t_env	*tmp;

	tmp = infos->env;
	if (exec->cmd_array[1])
	{
		ft_putstr_fd("pouetsh: env: too many arguments", 2);
		return (EXIT_FAILURE);
	}
	while (tmp)
	{
		if (tmp->value)
			print_keynvalue(outfile->fd, tmp);
		tmp = tmp->next;
	}
	return (0);
}
