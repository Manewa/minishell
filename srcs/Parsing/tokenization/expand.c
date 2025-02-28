/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:57:36 by namalier          #+#    #+#             */
/*   Updated: 2025/02/28 11:39:47 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/minishell.h"

/* Check_name will verify that there's not a infinite boucle.
 * For example :
 * $a = $b
 * $b = $a
 *
 * Problem : won't verify if $a = $b, $b = $c, $c = $a
 */

char *check_name(char *value, char *to_expand)
{
	size_t	i;
	char	*name_value;

	i = 0;
	while (value[i + 1] && to_expand[i] && value[i + 1] == to_expand[i])
	{
		i++;
	}
	if (!value[i + 1] && !to_expand[i])
	{
		i = 0;
		name_value = malloc(ft_strlen(value)*sizeof(char));
		if (!name_value)
			return (NULL);
		while (value[i + 1])
		{
			name_value[i] = value[i + 1];
			i++;
		}
		name_value[i] = '\0';
		free(value);
		return (name_value);
	}
	return (value);
}

/* expand_to_env will search for a key in infos->env (lst) and return the value associated to it.
 * if none is found, return NULL 
 * */

char *expand_to_env(char *to_expand, t_env *env)
{
	char 	*value;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		while (tmp &&
				(ft_memcmp(to_expand, tmp->key, ft_strlen(to_expand)+1)) != 0)
			tmp = tmp->next;
		if (tmp && ft_strlen(to_expand) == ft_strlen(tmp->key))
			break;
		else if (tmp)
			tmp = tmp->next;
	}
	if (tmp)
	{
		value = ft_strdup(tmp->value);
		value = check_name(value, to_expand);
		if (!value)
			return(NULL);
		return (value);
	}
	return (NULL);
}

/* Expanded_new_line will replace the old key by the value in infos->env found by expand_to_env.
 *
 * if none is found, delete the $KEY
 * Will free the old_line and the value and return the new line malloc
 */

char *expanded_new_line(char *old_line, int start, int end, char *expand)
{
	int		i;
	size_t	j;
	char	*new_line;

	i = 0;
	j = 0;
	if (!expand)
		new_line = malloc((ft_strlen(old_line) - (end - start) + 1)
				* sizeof(char));
	else
		new_line = malloc((ft_strlen(old_line) - (end - start)
					+ ft_strlen(expand) + 1)*sizeof(char));
	if (!new_line)
		return (NULL);
	while (i < start && old_line[i] != '$')
	{
		new_line[i] = old_line[i];
		i++;
	}
	while (expand && expand[j])
		new_line[i++] = expand[j++];
	while (old_line[end])
		new_line[i++] = old_line[end++];
	new_line[i] = '\0';
	free(old_line);
	free(expand);
	return (new_line);
}



/* Substitute expand defines start and end of an the expand to change ($USER for exemple)
 *
 * The expand run until finding anything else than alnum char or '_'
 * Return expand, the line with the expand.
 */

char *substitute_expand(char *line, t_infos *infos, int exp)
{
	int		end;
	size_t	j;
	int		start;
	char	*expand;

	start = exp;
	end = exp;
	j = 0;
	while (line[end] && (ft_isalnum(line[end]) == 1 || line[end] == '_'))
			end++;
	if (end != start)
		expand = malloc((end - start + 1)*sizeof(char));
	while (start < end)
		expand[j++] = line[start++];
	expand[j] = '\0';
	expand = expand_to_env(expand, infos->env);
	expand = expanded_new_line(line, exp - 1, end, expand);
	return (expand);
}

/* Main expand with rules :
 * line -> line where we search for a '$'
 * infos -> Env (lst) inside
 * 
 * -> If '$' is between quotes, is not verified
 * -> check for '$?' with exit_val in infos
 *
 *	While until the end of line and get back to 0 each time we find an expand
 *	to verify that there's no expand in an expand.
 *
 * Return line (with the new expand)
 */

char *expand_main(char *line, t_infos *infos)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 39)
			out_of_squote(line, &i);
		if (line[i] == '<' && line[i + 1] == '<')
			out_of_heredoc(line, &i);
		if (line[i] == '$' && line[i + 1] != '?')
		{
			line = substitute_expand(line, infos, ++i);
			if (!line)
				return (NULL);
			i = 0;
		}
		if (line[i] == '$' && line[i + 1] == '?')
		{
			line = expanded_new_line(line, i, i + 2, ft_itoa(infos->exit_val));
			i++;
			if  (!line)
				return (NULL);
		}
		if (line[i] && (line[0] != '$' || line[0] != 39))
			i++;
	}
	return (line);
}
