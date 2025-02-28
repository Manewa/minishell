/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:01:37 by namalier          #+#    #+#             */
/*   Updated: 2025/02/27 17:52:09 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Init_prompt is initiating the prompt ("minishell > ") with :
	- infos->line has the line gived by user
	- infos->s_in and s_out are respectively stdin (0) and stdout (1)
	- infos->env has the envp is existed */

int	init_prompt(t_infos *infos, char **envp)
{
	infos->line = readline("minishell> ");
	if (!infos->line)
		return (0);
	if (envp)
		infos->env = ft_cpyenv(envp);
	else

	if (!infos->env)
		return (0);
	return (1);
}
