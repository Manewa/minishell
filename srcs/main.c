/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:01:29 by namalier          #+#    #+#             */
/*   Updated: 2025/01/17 15:40:02 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_infos	infos;
	t_token	*token;

	(void)argv;
	if (argc!= 1)
		return (1);
	ft_lstnew(&infos);
	if (!ft_lstnew(&infos))
		return (1);
	if (init_prompt(&infos, envp) == 0)
		return (1);
	token = tokenization(&infos);
	token = tokens_for_exec(token);
	(void)token;
	return (0);
}
