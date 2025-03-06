/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:01:37 by namalier          #+#    #+#             */
/*   Updated: 2025/03/04 16:58:42 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Init_prompt is initiating the prompt ("minishell > ") with :
	- infos->line has the line gived by user
	- infos->env has the envp if existed */

int	init_prompt(t_infos *infos, char **envp)
{
	infos->line = readline("minishell> ");
	if (!infos->line)
		return (0);
	if (envp)
		infos->env = ft_cpyenv(envp);
	if (!infos->env)
		return (0);
	return (1);
}
