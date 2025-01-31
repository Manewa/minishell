/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_for_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:28:29 by namalier          #+#    #+#             */
/*   Updated: 2025/01/31 16:11:43 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/minishell.h"

int exec_type(t_exec *exec, t_token **current, t_token *head)
{
	if ((*current)->type == HEREDOC)
	{
		exec_heredoc(*current, exec);
		*current = (*current)->next;
	}
	else if (*current == head && (*current)->type == PIPE)
		return (0); /*Error : "zsh: parse error near `|'" si le premier charactere est un pipe*/
	else if ((*current)->type == PIPE)
		*current = (*current)-> next;
	while (*current && (*current)->type != HEREDOC && (*current)->type != PIPE)
	{
			if ((*current)->type == INREDIR)
				exec_inredir(*current, exec);
			else if ((*current)->type == OUTREDIR)
				exec_outredir(*current, exec);
			else if ((*current)->type == APPEND_MODE)
				exec_append(*current, exec);
			else if ((*current)->type == WORD)
				exec_word(*current, exec);
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

t_exec *exec_init(t_exec *head, t_token *current)
{
	t_exec	*exec;

	exec = ft_execnew(head);
	if (exec == NULL)
		return (NULL);
	if (head != 0)
		exec->head = head;
	else
		exec->head = NULL;
	exec->next = NULL;
	exec->files = ft_filenew();
	cpy_env_from_infos(current->infos, exec);
	ft_cpypath(current->infos, exec);
/*	if (current->infos->path)
		exec->path = ft_strdup(current->infos->path);
	else
		exec->path = malloc()*/
	return (exec);
}

t_exec	*tokens_for_exec(t_token *head_token)
{
	t_token	*current_token;
	t_exec	*head_exec;
	t_exec	*current_exec;
//	size_t	i;

	current_token = head_token;
	head_exec = exec_init(0, current_token);
	if (exec_type(head_exec, &current_token, head_token) == 0)
		return (0);
	while (current_token != NULL/* && current_token->next != NULL*/)
	{
		current_exec = exec_init(head_exec, current_token);
		if (!current_exec)
			return (NULL);
		if (current_token && current_token->type == PIPE)
		{
			current_token = current_token->next;
			free(current_token);
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
	




/*

		i = 0;
		if (current != lst_token)
			current = current->next;
		while (current->line_wip[i] && is_separator(current->line_wip[i] != 0))
			i++;
		if (!current->line_wip[i])
			return (NULL);
		if (current->type != PIPE)
		{
			current->token_line = split_off_quote(&i(current->line_wip[i]), ' ');
			quotes_detecter(current);
		}
		if (current->type == WORD)
			parse_word(current, i);
		else if (current->type == APPEND_MODE)
			parse_append(current, i);
		else if (current->type == HEREDOC)
			parse_heredoc(current, i);
		else if (current->type == OUTREDIR)
			parse_outredir(current, i);
		else if (current->type == INREDIR)
			parse_inredir(current, i);
	}
}*/
