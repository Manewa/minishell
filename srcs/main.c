/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:01:29 by namalier          #+#    #+#             */
/*   Updated: 2025/01/30 16:21:10 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_infos	infos;
	t_token	*token;
	t_exec	*to_exec;

	int i = 0;


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
	while (to_exec->next)
	{
		printf("IN DA WHILE !!!!!!!!!!!!\n");
		if (to_exec->is_heredoc == OUI)
			printf("heredoc : |%s|\n", to_exec->delimiter);
/*		if (to_exec->path[i])
		{
			while (to_exec->path[i])
			{
				printf("path : |%s|\n", to_exec->path[i]);
				i++;
			}
		}
		else
			printf("NO PATH FOUND\n");
		i = 0;
		if (to_exec && to_exec->path && to_exec->path[i])
		{
			while (to_exec->env[i])
			{
				printf("env : |%s|\n", to_exec->env[i]);
				i++;
			}
		}
		else
			printf("NO ENV FOUND\n");
*/		i = 0;
		while (to_exec && to_exec->cmd_array && to_exec->cmd_array[i])
		{
			printf("cmd_array : |%s|\n", to_exec->cmd_array[i]);
			i++;
		}
		if (to_exec && to_exec->files && to_exec->files->infile && to_exec->files->infile->name)
			printf ("infile : %s\n", to_exec->files->infile->name);
		if (to_exec && to_exec->files && to_exec->files->outfile && to_exec->files->outfile->name)
			printf ("outfile : %s\n", to_exec->files->outfile->name);
		to_exec = to_exec->next;
	}
	printf("\n\nOUT OF DA WHILE !!!!\n\n");
	if (to_exec->is_heredoc == 1)
		printf("heredoc : |%s|\n", to_exec->delimiter);
/*	if (to_exec && to_exec->path && to_exec->path[i])
	{
		while (to_exec->path[i])
		{
			printf("path : |%s|\n", to_exec->path[i]);
			i++;
		}
	}
	else
		printf("NO PATH FOUND");
	i = 0;
	if (to_exec->env[i])
	{
		while (to_exec->env[i])
		{
			printf("env : |%s|\n", to_exec->env[i]);
			i++;
		}
	}
	else
		printf("NO ENV FOUND");
*/	i = 0;
	while (to_exec && to_exec->cmd_array && to_exec->cmd_array[i])
	{
		printf("cmd_array : |%s|\n", to_exec->cmd_array[i]);
		i++;
	}
	if (to_exec && to_exec->files && to_exec->files->infile && to_exec->files->infile->name)
		printf ("infile : %s\n", to_exec->files->infile->name);
	if (to_exec && to_exec->files && to_exec->files->outfile && to_exec->files->outfile->name)
		printf ("outfile : %s\n", to_exec->files->outfile->name);
	return (0);
}
