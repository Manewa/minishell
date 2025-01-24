/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:01:29 by namalier          #+#    #+#             */
/*   Updated: 2025/01/24 14:19:11 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_infos	infos;
	t_token	*token;
	t_exec	*to_exec;

	(void)argv;
	if (argc!= 1)
		return (1);
	ft_lstnew(&infos);
	if (!ft_lstnew(&infos))
		return (1);
	if (init_prompt(&infos, envp) == 0)
		return (1);
	token = tokenization(&infos);
	to_exec = tokens_for_exec(token);
	while (token->next)
	{
		printf("path : |%s| // line : %d\n", token->full_path, token->type);
		token = token->next;
	}
	printf("line : |%s| // type : %d\n", token->line_wip, token->type);
	return (0);
}
