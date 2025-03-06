/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_for_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:28:29 by namalier          #+#    #+#             */
/*   Updated: 2025/03/06 20:04:43 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/minishell.h"

/*
 * for each type, redirect to the right exec_type function
 */

int exec_type(t_exec *exec, t_token **current, t_token *head)
{
	if (*current == head && (*current)->type == PIPE)
		return (0); /*Error : "zsh: parse error near `|'" si le premier charactere est un pipe*/
	while (*current && (*current)->type != PIPE)
	{
			if ((*current)->type == INREDIR)
				exec_inredir(*current, exec);
			else if ((*current)->type == OUTREDIR)
				exec_outredir(*current, exec);
			else if ((*current)->type == APPEND_MODE)
				exec_append(*current, exec);
			else if ((*current)->type == WORD)
				exec_word(*current, exec);
			else if ((*current)->type == HEREDOC)
				exec_heredoc(*current, exec);
			if ((*current) && (*current)->next != NULL)
				*current = (*current)->next;
			else
			{
				free (*current);
				*current = NULL;
			}
	}
	return (1);
}

/*
 * Initialize the exec node
 */

t_exec *exec_init(t_exec *head, t_token *current)
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
	ft_cpypath(current->infos, exec);
	return (exec);
}

t_exec	*tokens_for_exec(t_token *head_token)
{
	t_token	*current_token;
	t_exec	*head_exec;
	t_exec	*current_exec;

	current_token = head_token;
	head_exec = exec_init(0, current_token);
	head_exec->env = env_double_tab(head_exec->infos->env);
	if (exec_type(head_exec, &current_token, head_token) == 0)
		return (0);
	while (current_token != NULL/* && current_token->next != NULL*/)
	{
		current_exec = exec_init(head_exec, current_token);
		current_exec->env = current_exec->head->env;
		if (!current_exec)
			return (NULL);
		if (current_token && current_token->type == PIPE)
		{
			current_token = current_token->next;
			continue ;
		}
		if (exec_type(current_exec, &current_token, head_token) == 0)
			return (0);
		ft_execadd_back(&head_exec, current_exec);
		if (current_token && current_token->next != NULL && current_token->type != 5)
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

	token = tokenization(infos);
	exec = tokens_for_exec(token);
//	ft_free_token(token);
	return (exec);
}
