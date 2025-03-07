/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <aibonade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:22:19 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/06 20:11:12 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void ft_del_file(t_fdata *file)
{
	if (file->name && file->heredoc != YES)//si infile = heredoc, penser a unlink heredoc
		free(file->name);
	else if (file->heredoc == YES)
		unlink(file->name);
	free(file);
}

static void ft_free_files(t_files *files)
{
	ft_del_file(files->infile);
	ft_del_file(files->outfile);
	free(files);
}

static void ft_free_heredoc_lst(t_lim *lim)
{
	t_lim	*current;
	t_lim	*nxt;

	current = lim;
	while (current)
	{
		nxt = current->next;
		free(current->h_name);
		free(current);
		current = nxt;
	}
}

void ft_free_dbltab(char **str)
{
	size_t	i;

	if (str)
	{
		i = 0;
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

static void ft_delone_exec(t_exec *exec)
{
	if (exec)
	{
		ft_free_files(exec->files);
		if (exec->is_heredoc)
			ft_free_heredoc_lst(exec->limiter);
		ft_free_dbltab(exec->cmd_array);
		free(exec);
		exec = NULL;
	}
}

void ft_clean_end_exec(t_exec *exec)
{
	t_exec	*tmp;
	t_exec	*tmp_nxt;

	if (exec)
	{
		tmp = exec;
		tmp_nxt = tmp->next;
		ft_free_dbltab(tmp->path);
		ft_free_dbltab(tmp->env);
		ft_delone_exec(tmp);
		while (tmp_nxt)
		{
			tmp = tmp_nxt;
			tmp_nxt = tmp->next;
			ft_delone_exec(tmp);
		}
		exec = NULL;
	}

}
