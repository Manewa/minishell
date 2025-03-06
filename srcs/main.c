/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:01:29 by namalier          #+#    #+#             */
/*   Updated: 2025/03/06 18:44:13 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	sig_global;

int main(int argc, char **argv, char **envp)
{
	t_infos	*infos;
	t_exec	*exec;

	(void)argv;
	if (argc != 1 || ft_infonew(&infos, envp))
		return (1);
	while(infos->pouexit)
	{
		//set_signal(infos);
		if (infos->line)
			free(infos->line);
		infos->line = readline("MiniPouet> ");
		if (infos->line && infos->line[0] && infos->line[0] != ' ')
			add_history(infos->line);
		exec = main_parsing(infos);
		if (!exec)
			continue ;
		ft_main_exec(exec);
	}
	free(infos->line);
	rl_clear_history();
	return (0);
}



/*int main(int argc, char **argv, char **envp)
{
	t_infos	infos;
	t_token	*token;
	t_exec	*to_exec;

//	int i = 0;


	(void)argv;
	if (argc!= 1)
		return (1);
	if (!ft_lstnew(&infos))
	return (1);
	infos.exit_val = 0;
	if (init_prompt(&infos, envp) == 0)
		return (1);
	set_signal(&infos);
	infos.exit_val = 0;
	token = tokenization(&infos);
	to_exec = tokens_for_exec(token);
	ft_main_exec(to_exec);
}

// void test_parsing(t_infos *infos, t_exec *to_exec)
// {
// 	while (to_exec && to_exec->next)
// 	{
// 		printf("IN DA WHILE !!!!!!!!!!!!\n");
// 		if (to_exec->is_heredoc >= YES)
// 		{
// 			while(to_exec->limiter && to_exec->limiter->next)
// 			{
// 				printf("heredoc : |%s| |||| Quotes :%d\n", to_exec->limiter->limit, to_exec->limiter->quotes);
// 				to_exec->limiter = to_exec->limiter->next;
// 			}
// 			printf("heredoc : |%s| |||| Quotes :%d\n", to_exec->limiter->limit, to_exec->limiter->quotes);
// 		}	
		if (to_exec->path[i])
// 		{
// 			while (to_exec->path[i])
// 			{
// 				printf("path : |%s|\n", to_exec->path[i]);
// 				i++;
// 			}
// 		}
// 		else
// 			printf("NO PATH FOUND\n");
// 		i = 0;
// 		if (to_exec && to_exec->env)
// 		{
// 			while (to_exec->env[i])
// 			{
// 				printf("env : |%s|\n", to_exec->env[i]);
// 				i++;
// 			}
// 		}
// 		else
// 			printf("NO ENV FOUND\n");
// 		i = 0;
// 		if (to_exec->builtin != 0)
// 			printf("Builtin numero : %d\n", to_exec->builtin);
// 		while (to_exec && to_exec->cmd_array && to_exec->cmd_array[i])
// 		{
// 			printf("cmd_array[%d] : |%s|\n", i, to_exec->cmd_array[i]);
// 			i++;
// 		}
// 		if (to_exec && to_exec->files && to_exec->files->infile && to_exec->files->infile->name)
// 			printf ("infile : %s\n", to_exec->files->infile->name);
// 		if (to_exec && to_exec->files && to_exec->files->outfile && to_exec->files->outfile->name)
// 			printf ("outfile : %s\n", to_exec->files->outfile->name);
// 		to_exec = to_exec->next;
// 	}
// 	printf("\n\nOUT OF DA WHILE !!!!\n\n");
// 	if (to_exec->is_heredoc >= YES)
// 	{
// 		while(to_exec->limiter && to_exec->limiter->next)
// 		{
// 			printf("heredoc : |%s| |||| Quotes :%d\n", to_exec->limiter->limit, to_exec->limiter->quotes);
// 			to_exec->limiter = to_exec->limiter->next;
// 		}
// 		printf("heredoc : |%s| |||| Quotes :%d\n", to_exec->limiter->limit, to_exec->limiter->quotes);
// 	}	
// 	if (to_exec && to_exec->path && to_exec->path[i])
// 	{
// 		while (to_exec->path[i])
// 		{
// 			printf("path : |%s|\n", to_exec->path[i]);
// 			i++;
// 		}
// 	}
// 	else
// 		printf("NO PATH FOUND");
// 	i = 0;
// 	if (to_exec->env[i])
// 	{
// 		while (to_exec->env[i])
// 		{
// 			printf("env : |%s|\n", to_exec->env[i]);
// 			i++;
// 		}
// 	}
// 	else
// 		printf("NO ENV FOUND");
// 	i = 0;
// 	if (to_exec->builtin != 0)
// 		printf("Builtin numero : %d\n", to_exec->builtin);
// 	while (to_exec && to_exec->cmd_array && to_exec->cmd_array[i])
// 	{
// 		printf("cmd_array[%d] : |%s|\n", i, to_exec->cmd_array[i]);
// 		i++;
// 	}
// 	if (to_exec && to_exec->files && to_exec->files->infile && to_exec->files->infile->name)
// 		printf ("infile : %s\n", to_exec->files->infile->name);
// 	if (to_exec && to_exec->files && to_exec->files->outfile && to_exec->files->outfile->name)
// 		printf ("outfile : %s\n", to_exec->files->outfile->name);
// 	return (0);
// }*/
