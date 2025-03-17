/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:22:59 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/17 16:02:24 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_var(t_env **head, char *unset)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	while (current)
	{
		if (ft_strcmp(current->key, unset) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			break;
		}
		prev = current;
		current = current->next;
	}
}

int	check_var_name(char *str)
{
	size_t	i;

	i = 1;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i])
		return (1);
	return (0);
}
int	ft_unset(t_exec *exec, int fd_out)
{
	size_t	i;
	int		errno;

	errno = 0;
	i = 1;
	while (exec->cmd_array[i])
	{
		if ((ft_isalpha(exec->cmd_array[i][0]) || exec->cmd_array[i][0] == '_')
				&& !check_var_name(exec->cmd_array[i]))
			unset_var(&(exec->infos->env), exec->cmd_array[i]);
		else
		{
			write(fd_out, "pouetsh: unset: `", 17);
			write(fd_out, exec->cmd_array[i], ft_safe_strlen(exec->cmd_array[i]));
			write(fd_out, "': not a valid identifier\n", 27);
			errno = 1;
		}
		i++;
	}
	return (errno);
}
