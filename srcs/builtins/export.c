/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:41:09 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/16 18:05:55 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_key(t_env *new, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(new->key, tmp->key) == 0)
		{
			free(new->key);
			free(new);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	add_to_env(t_env **head, char *str)
{
	size_t	i;
	size_t	j;
	t_env	*new;

	i = 0;
	j = 0;
	new = ft_envnew(0);
	while (str[i] && str[i] != '=')
			i++;
	new->key = malloc((i + 1) * sizeof(char));
	if (!new->key)
		return ;
	while(j < i)
	{
		new->key[j] = str[j];
		j++;
	}
	if (!check_key(new, *head))
		return ;
	new->key[j++] = '\0';
	new->value = ft_strdup(&(str[j]));
	*head = insert_sorted(*head, new);
}

int	check_var(char *var)
{
	size_t	i;

	i = 0;
	while (var[i] && var[i] != '=')
	{
		if ((i == 0 && !ft_isalnum(var[i]))
				|| (!ft_isalnum(var[i]) && var[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}

void	write_env(t_env *head, int fd_out)
{
	t_env	*current;

	current = head;
	while (current)
	{
		ft_putstr_fd("declare -x ", fd_out);
		write(fd_out, current->key, ft_safe_strlen(current->key));
		write(fd_out, "=", 1);
		if (current->value)
		{
			write (fd_out, "\"", 1);
			write (fd_out, current->value, ft_safe_strlen(current->value));
			write (fd_out, "\"", 1);
		}
		write (fd_out, "\n", 1);
		current = current->next;
	}
}

int	ft_export(t_exec *exec, int fd_out)
{
	size_t	i;
	int		errno;

	i = 1;
	errno = 0;
	if (!exec->cmd_array[1])
		write_env(exec->infos->env, fd_out);
	else
	{
		while (exec->cmd_array[i])
		{
			if (check_var(exec->cmd_array[i]))
				add_to_env(&(exec->infos->env), exec->cmd_array[i]);
			else if (errno == 0)
				errno = i;
			i++;
		}
	}
	if (errno != 0)
	{
		write (2, "pouetsh: export: `", 17);
		write (2, exec->cmd_array[errno],
				ft_safe_strlen(exec->cmd_array[errno]));
		write (2,  "': not a valid identifier", 25);
		return (1);
	}
	return (0);
}
