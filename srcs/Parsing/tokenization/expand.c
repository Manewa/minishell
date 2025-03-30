/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:57:36 by namalier          #+#    #+#             */
/*   Updated: 2025/03/30 16:51:33 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*check_name(char *value, char *to_expand)
{
	size_t	i;
	char	*name_value;

	i = 0;
	while (value[i + 1] && to_expand[i] && value[i + 1] == to_expand[i])
		i++;
	if (!value[i + 1] && !to_expand[i])
	{
		i = 0;
		name_value = malloc(ft_strlen(value) * sizeof(char));
		if (!name_value)
		{
			free (value);
			free (to_expand);
			return (NULL);
		}
		while (value[i + 1])
		{
			name_value[i] = value[i + 1];
			i++;
		}
		name_value[i] = '\0';
		return (free(value), free(to_expand), name_value);
	}
	return (free(to_expand), value);
}

static t_env	*get_node_key(t_env *tmp, char *to_expand)
{
	while (tmp)
	{
		while (tmp && (ft_memcmp(to_expand,
					tmp->key, ft_strlen(to_expand) + 1)) != 0)
			tmp = tmp->next;
		if (tmp && ft_strlen(to_expand) == ft_strlen(tmp->key))
			break ;
		else if (tmp)
			tmp = tmp->next;
	}
	return (tmp);
}

/* expand_to_env will search for a key in infos->env (lst) and return the value
 * associated to it.
 * if none is found, return NULL 
 * */

char	*expand_to_env(char *to_expand, t_env *env)
{
	char	*value;
	t_env	*tmp;

	tmp = env;
	tmp = get_node_key(tmp, to_expand);
	if (tmp)
	{
		value = ft_strdup(tmp->value);
		if (!value)
			return (NULL);
		value = check_name(value, to_expand);
		if (!value)
			return (NULL);
		return (value);
	}
	free (to_expand);
	to_expand = malloc (1 * sizeof(char));
	if (!to_expand)
		return (NULL);
	to_expand[0] = '\0';
	return (to_expand);
}

static char	*cp_extended_new_line(int start, int end, char *old, char *expand)
{
	int		i;
	char	*new;

	i = 0;
	if (!expand)
		new = malloc((ft_strlen(old) - (end - start) + 1)
				* sizeof(char));
	else
		new = malloc((ft_strlen(old) - (end - start)
					+ ft_strlen(expand) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = cpy_part_line(old, expand, start, new);
	while (old[end])
		new[i++] = old[end++];
	new[i] = '\0';
	return (new);
}

/* Expanded_new_line will replace the old key by the value in infos->env
 * found by expand_to_env.
 *
 * if none is found, delete the $KEY
 * Will free the old_line and the value and return the new line malloc
 */

char	*expanded_new_line(char *old_line, int start, int end, char *expand)
{
	char	*new_line;

	new_line = cp_extended_new_line(start, end, old_line, expand);
	if (!new_line)
	{
		if (expand)
			free(expand);
		return (free(old_line), NULL);
	}
	return (free(old_line), free(expand), new_line);
}
