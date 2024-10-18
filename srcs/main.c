/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:01:29 by namalier          #+#    #+#             */
/*   Updated: 2024/10/18 17:37:52 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main (int argc, char **argv, char **envp)
{
	t_infos	infos;

	if (argc!= 1)
		return (1);
	(void)argv;
	ft_lstnew(&infos);
	if (!ft_lstnew(&infos))
		return (1);
	if (!init_prompt(&infos, envp))
		return (1);
	return (0);
}
