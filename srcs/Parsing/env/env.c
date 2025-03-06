/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:10:04 by namalier          #+#    #+#             */
/*   Updated: 2025/03/04 11:47:32 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
 * copy the path in exec, removing "PATH="
 */

void ft_cpypath(t_infos *infos, t_exec *exec)
{
	t_env	*tmp;

	tmp = infos->env;
	if (!infos->env)
		return ;
	while (tmp && ft_strnstr(tmp->key, "PATH", 4) == 0)
		tmp = tmp->next;
	if (!tmp)
		return ;
	exec->path = ft_split(tmp->value, ':');
	if (!(exec->path))
		return ;
}

/*
 * dissociating key and value from envp to store it in env lst
 */

void env_key_n_value(t_env *env, char **envp, size_t i)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (envp[i] && envp[i][j] && envp[i][j] != '=')
		j++;
	env->key = malloc(j * sizeof(char));
	if (!env->key)
		return ;
	while(k < j)
	{
		env->key[k] = envp[i][k];
		k++;
	}
	env->key[k++] = '\0';
	j++;
	env->value = ft_strdup(&(envp[i][k]));
}

/* cpyenv is copying char **envp to infos->env in a list */

t_env	*ft_cpyenv(char **envp)
{
	size_t	i;
	t_env	*head;
	t_env	*current;
	t_env	*prev;

	i = 0;
	head = ft_envnew(NULL);
	env_key_n_value(head, envp, i);
	prev = head;
	i++;
	while (envp[i])
	{
		current = ft_envnew(prev);
		ft_envadd_back(&head, current);
		prev = current;
		env_key_n_value(current, envp, i);
		i++;
	}
	return (head);
}

int len_env_line(t_env *tmp)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(tmp->key);
	j = ft_strlen(tmp->value);
	return (i + j + 2);
}

/*
 * adding "key" + "=" + "value" in to_exec->env
 */

void cat_key_n_value(t_env *tmp, char **tab, size_t i)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;

	tab[i] = malloc(len_env_line(tmp) * sizeof(char));
	if (!tab[i])
		return ;
	while (tmp->key[j])
	{
		tab[i][j] = tmp->key[j];
		j++;
	}
	tab[i][j++] = '=';
	while (tmp->value[k])
		tab[i][j++] = tmp->value[k++];
	tab[i][j] = '\0';
}

/*
 * create a double char array to to_exec->env, passing the env list to it
 */

char	**env_double_tab(t_env *env)
{
	size_t	i;
	t_env	*tmp;
	char	**tab;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp  = tmp->next;
	}
	tmp = env;
	tab = malloc((i + 1)*sizeof(char*));
	if (!tab)
		return (NULL);
	i = 0;
	while (tmp)
	{
		cat_key_n_value(tmp, tab, i);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}
