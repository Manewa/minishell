/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:25:01 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/18 12:33:09 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/minishell.h"

void ft_lstenvfree(t_env *env)
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

void *ft_free_token(t_token *token)
{
	t_token *tmp;

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

void *ft_free_infoken(t_infos *infos, t_token *token, char *error, int exit_prg)
{
	if (token)
		ft_free_token(token);
	if (infos)
		ft_free_infos(infos, error, exit_prg);
	return (NULL);
}

void *ft_error_parsing(t_infos *infos, t_token *token, char c)
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

void *ft_exit_exec(t_token *token, t_exec *head_exec, int exit_prg)
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

void ft_free_files_parsing(t_files *files)
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

void ft_free_limiter(t_lim *lim)
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
