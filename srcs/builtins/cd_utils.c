/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <aibonade@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:45:25 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/29 18:46:03 by aibonade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_chdir(t_exec *exec)
{
	if (chdir(exec->cmd_array[1]) == -1)
	{
		ft_putstr_fd("minipouet: ", 2);
		ft_putstr_fd(exec->cmd_array[0], 2);
		ft_putstr_fd(": ", 2);
		perror(exec->cmd_array[1]);
		return (1);
	}
	return (0);
}

t_env	*ft_get_env_value(t_env *tmp, char *to_find, int len)
{
	while (tmp && ft_strncmp(tmp->key, to_find, len))
		tmp = tmp->next;
	return (tmp);
}
