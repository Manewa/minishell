/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_for_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:28:29 by namalier          #+#    #+#             */
/*   Updated: 2025/03/30 16:30:19 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
 * for each type, redirect to the right exec_type function
 */

int	exec_type(t_exec *exec, t_token **current)
{
	while (*current && (*current)->type != PIPE)
	{
		if ((*current)->type == INREDIR)
			exec_inredir(current, exec);
		else if ((*current)->type == OUTREDIR)
			exec_outredir(current, exec);
		else if ((*current)->type == APPEND_MODE)
			exec_append(current, exec);
		else if ((*current)->type == WORD)
			exec_word(*current, exec);
		else if ((*current)->type == HEREDOC)
			exec_heredoc(*current, exec);
		if ((*current) && (*current)->next != NULL)
			*current = (*current)->next;
		else if ((*current) && (*current)->next == NULL)
		{
			*current = NULL;
			break ;
		}
	}
	return (1);
}

/*
 * Initialize the exec node
 */

t_exec	*exec_init(t_exec *head, t_token *current)
{
	t_exec	*exec;

	exec = ft_execnew(head, current->infos);
	if (exec == NULL)
		return (NULL);
	if (head != 0)
		exec->head = head;
	else
		exec->head = exec;
	exec->next = NULL;
	exec->files = ft_filenew();
	if (!(exec->head->path))
		ft_cpypath(current->infos, exec);
	else
		exec->path = exec->head->path;
	return (exec);
}

static int	add_exec_node(t_exec *head_exec, t_token **token)
{
	t_exec	*current_exec;

	if (*token && (*token)->type == PIPE)
	{
		*token = (*token)->next;
		return (1);
	}
	current_exec = exec_init(head_exec, *token);
	if (!current_exec)
		ft_exit_exec((*token)->head, head_exec, 1);
	current_exec->env = current_exec->head->env;
	if ((*token)->line_wip && (*token)->line_wip[0])
		exec_type(current_exec, token);
	ft_execadd_back(&head_exec, current_exec);
	return (0);
}

t_exec	*tokens_for_exec(t_token *head_token)
{
	t_token	*current_token;
	t_exec	*head_exec;

	current_token = head_token;
	head_exec = exec_init(0, current_token);
	if (!head_exec)
		ft_exit_exec(head_token, head_exec, 1);
	head_exec->env = env_double_tab(head_exec->infos->env);
	if (!head_exec->env)
		ft_exit_exec(head_token, head_exec, 1);
	if (head_token->line_wip && head_token->line_wip[0])
		exec_type(head_exec, &current_token);
	while (current_token != NULL)
	{
		if (add_exec_node(head_exec, &current_token) == 1)
			continue ;
		if (current_token && current_token->next != NULL
			&& current_token->type != 5)
			current_token = current_token->next;
		else if (current_token && current_token->type == 5)
			continue ;
		else
			break ;
	}
	return (head_exec);
}

t_exec	*main_parsing(t_infos *infos)
{
	t_token	*token;
	t_exec	*exec;

	if (!check_quotes(infos->line))
		return (ft_free_infos(infos, 0, 0));
	token = tokenization(infos);
	if (!token)
		return (NULL);
	exec = tokens_for_exec(token);
	if (!exec)
		return (NULL);
	if (infos->line)
		free(infos->line);
	ft_free_token(token);
	return (exec);
}
