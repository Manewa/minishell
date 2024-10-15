/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:01:37 by namalier          #+#    #+#             */
/*   Updated: 2024/10/15 18:15:59 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_prompt(s_infos *infos, char **envp)
{
	infos->s_in = dup(0);
	infos->s_out = dup(1);
	infos->line = readline(PROMPT);
	infos->env = ft_cpyenv(infos, envp);
	if (!infos->line)
		return (NULL);
}
