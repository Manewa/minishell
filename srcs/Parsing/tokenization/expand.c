/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:57:36 by namalier          #+#    #+#             */
/*   Updated: 2024/12/11 18:49:30 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* expand_env va expand la valeur de l'environnement et free to_expand dont on n'auraplus besoin
 */

void expand_env(char *env, char *to_expand, size_t j)
{
	char *expanded;
	size_t	i;
	
	i = j;
	while (env[i])
		i++;
	expanded = malloc((i + 1)*sizeof(char));
	i = 0;
	while (env[j])
	{
		expanded[i] = env[j];
		i++;
		j++;
	}
	expanded[i] = '\0';
	free (to_expand);
	return (expanded);
}

/* Foction en deux temps :
 * dans un premier temps, to_expand a la valeur a expand ($PATH par exemple)
 * il va checker dans l'env toutes les possibilites afin de trouver la bonne correspondance
 *
 * Dans un deuxieme temps, to_expand va prendre la valeur de la nouvelle line a expand
 * donc la valeur de PATH soit /dev/bin /dev etc.
 *
 * si pas de correspondance, return un \0 afin de remplacer par rien un expand rate
 */

char *expand_find_env(t_infos *infos, char *to_expand)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (infos->env[i])
	{
		j = 0;
		k = 1;
		while (infos->env[i][j] && to_expand[k]
				&& infos->env[i][j] == to_expand[k])
		{
			j++;
			k++;
		}
		if (!to_expand[k] && infos->env[i][j] == '=')
			break ;
		i++;
	}
	if (infos->env[i])
		to_expand = expand_env(infos->env[i], to_expand, j);
	else 
	{
		free (to_expand);
		return ("\0");
	}
	return (to_expand);
}

/* Va tranformer l'expand et return la valeur de la variable dans env
 */

char *expanded_new_line(char *old_line, t_infos *infos, char *to_expand)
{
	size_t	i;
	size_t	j;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = expand_find_env(token->infos, to_expand);
}

/* Permet de trouver a fin de l'expand puis de transformer en la ouvelle line
 * avec l'expand
 */

char *get_to_expand(char *line, t_token *token, int *start)
{
	size_t	end;
	size_t	j;
	char	*to_expand;

	(*i)++;
	end = *i;
	j = 0;
	while (line[end] && (ft_isalnum(line[end]) == 1 || line[end] != '_'))
			end++;
	if (end != *start)
		str = malloc((end - *i + 1)*sizeof(char));
	while (*i < end)
		to_expand[j++] = line[*i++];
	to_expand[j] = '\0';
	to_expand = expanded_new_line(line, token, to_expand);
	return (to_expand);
}

/* C'est la machine a expand :
 * part_of_line -> la partie de la line envoye a minishell qui vaut pour le token en cours
 * Va expand dans une double boucle while pour etre sur de ne pas rater
 * 		un expand qui se situerai dans un autre expand
 */

char *expander_over_9000(char *part_of_line, t_token *token)
{
	int		i;
	size_t	j;
	char	*str;


	i = 0;
	j = 0;
	while (part_of_line[i])
	{
		if (part_of_line[i] == 39)
			out_of_squote(part_of_line, &readed);
		if (part_of_line[i] == '$')
		{
			while (
		}
	}
}
