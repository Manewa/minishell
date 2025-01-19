/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:57:36 by namalier          #+#    #+#             */
/*   Updated: 2025/01/14 17:29:47 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/minishell.h"

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

/* expand_to_env va expand la valeur de l'environnement et free to_expand
   dont on n'aura plus besoin */

char *expand_to_env(char *line, t_infos *infos, char *to_expand, char **env)
{
	char *value;
	size_t	i;
	size_t	j;
	size_t	k;

	(void)line;
	i = 0;
	while (env[i])
	{
		j = 0;
		k = 0;
		while (infos->env[i][j] && to_expand[k]
				&& infos->env[i][j] == to_expand[k++])
			j++;
		if (!to_expand[k] && infos->env[i][j] == '=')
			break ;
		i++;
	}
	if (env[i])
	{
		value = ft_strdup(&env[i][j + 1]);
		value = check_name(value, to_expand);
		if (!value)
			return(NULL);
		return (value);
	}
	return (NULL);
}

/* Va free l'ancienne line avec expand et return la nouvelle line avec la
	nouvelle valeur de l'expand
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



/* Permet de trouver a fin de l'expand puis de transformer en la nouvelle line
 * avec l'expand
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
	expand = expand_to_env(line, infos, expand, infos->env);
	expand = expanded_new_line(line, exp - 1, end, expand);
	return (expand);
}

/* C'est la machine a expand :
 * part_of_line -> la partie de la line envoye a minishell qui vaut pour le token en cours
 * Va expand dans une double boucle while pour etre sur de ne pas rater
 * 		un expand qui se situerai dans un autre expand
 */

char *expand_main(char *line, t_infos *infos)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 39)
			out_of_squote(line, 0);
		if (line[i] == '$')
		{
			line = substitute_expand(line, infos, ++i);
			if (!line)
				return (NULL);
			i = 0;
		}
		if (line[i] && (line[0] != '$' || line[0] != 39))
			i++;
	}
	i = 0;
	printf("line : %s\n", line);
	return (line);
}
