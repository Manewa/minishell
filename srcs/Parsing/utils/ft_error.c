/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:25:01 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/29 01:13:45 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_lstenvfree(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->value)
			free(env->value);
		if (env->key)
			free(env->key);
		free(env);
		env = tmp;
	}
}

void	*ft_free_infos(t_infos *infos, char *error, int exit_prg)
{
	int	ex;

	if (exit_prg == -1)
		ex = infos->exit_val;
	if (exit_prg != 0 && infos->line)
		free(infos->line);
	if (infos->env && exit_prg != 0)
		ft_lstenvfree(infos->env);
	if (infos && exit_prg != 0)
		free(infos);
	if (error)
		ft_putstr_fd(error, 2);
	if (exit_prg > 0)
		exit (exit_prg);
	else if (exit_prg == -1)
	{
		write(2, "exit\n", 5);
		exit(ex);
	}
	return (NULL);
}

void	*ft_free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->line_wip)
			free(token->line_wip);
		free(token);
		token = tmp;
	}
	return (NULL);
}

void	*ft_free_infoken(t_infos *infos, t_token *token, char *error, int exit)
{
	if (token)
		ft_free_token(token);
	if (infos)
		ft_free_infos(infos, error, exit);
	return (NULL);
}
