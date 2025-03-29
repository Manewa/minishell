/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 01:13:34 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/29 01:13:36 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	*ft_error_parsing(t_infos *infos, t_token *token, char c)
{
	ft_putstr_fd("pouetsh : syntax error near unexpected token `", 2);
	if (c)
		write (2, &c, 1);
	else
		write (1, "newline", 7);
	write (2, "'\n", 2);
	infos->exit_val = 2;
	ft_free_infoken(infos, token, 0, 0);
	return (NULL);
}

void	*ft_exit_exec(t_token *token, t_exec *head_exec, int exit_prg)
{
	t_exec	*exec;

	ft_free_infoken(head_exec->infos, token, "pouetsh: Can't malloc\n", 0);
	while (head_exec)
	{
		exec = head_exec;
		if (exec->files)
			ft_free_files_parsing(exec->files);
		if (exec->limiter)
			ft_free_limiter(exec->limiter);
		if (exec->path)
			ft_free_doubletab(exec->path);
		if (exec->env)
			ft_free_doubletab(exec->env);
		if (exec->cmd_array)
			ft_free_doubletab(exec->cmd_array);
		if (exec->cmd_path)
			free(exec->cmd_path);
		head_exec = head_exec->next;
		free (exec);
	}
	if (exit_prg != 0)
		exit(exit_prg);
	return (NULL);
}

void	ft_free_files_parsing(t_files *files)
{
	if (files->infile)
	{
		if (files->infile->name)
			free (files->infile->name);
		free (files->infile);
	}
	if (files->outfile)
	{
		if (files->outfile->name)
			free (files->outfile->name);
		free (files->outfile);
	}
	free (files);
}

void	ft_free_limiter(t_lim *lim)
{
	t_lim	*tmp;

	tmp = lim;
	while (lim)
	{
		tmp = lim;
		if (tmp->limit)
			free(tmp->limit);
		if (tmp->h_name)
			free(tmp->h_name);
		lim = lim->next;
		free (tmp);
	}
}
