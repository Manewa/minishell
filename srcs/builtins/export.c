/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:41:09 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/15 19:14:38 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sort_env_write(t_exec *exec, t_env *env, int fd_out)
{
	int 	end;
	t_env	*tmp;
	t_env	*print;

	tmp = env;
	end = 0;
	print = NULL;
	while (end == 1)
	{
		end = 0;
		while (tmp);
		{
			
		}

	}
}

int	ft_export(t_exec *exec, int fd_out)
{
	if (!exec->cmd_array[1])
		sort_env_print(exec, exec->infos, fd_out);
}
