/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:01:45 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/04 18:36:44 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_strcmp(char *line, char *builtin)
{
	size_t	i;

	i = 0;
	while (line[i] == builtin[i] && line[i] && builtin[i])
		i++;
	return (line[i] - builtin[i]);
}

/*
 * return an int, alias in minishell.h stored in to_exec->builtin
 */

int builtin_cmp(char *line)
{
	if (ft_strcmp(line, "echo") == 0)
		return (ECHO);
	else if (ft_strcmp(line, "cd") == 0)
		return (CD);
	else if (ft_strcmp(line, "pwd") == 0)
		return (PWD);
	else if (ft_strcmp(line, "export") == 0)
		return (EXPORT);
	else if (ft_strcmp(line, "unset") == 0)
		return (UNSET);
	else if (ft_strcmp(line, "env") == 0)
		return (ENV);
	else if (ft_strcmp(line, "exit") == 0)
		return (EXIT);
	else
		return (0);
}

/*
 * Checking builtin for every cmd_array[0] of each node of exec
 */

/*void check_builtin(t_exec *head_exec)
{
	t_exec	*tmp;

	tmp = head_exec;
	while (tmp)
	{
		tmp->builtin = builtin_cmp(tmp->cmd_array[0]);
		tmp = tmp->next;
	}	
}*/
