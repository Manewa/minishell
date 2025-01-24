/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_for_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:28:29 by namalier          #+#    #+#             */
/*   Updated: 2025/01/24 17:56:49 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int exec_type(t_exec *exec, t_token *start, t_token *head)
{
	size_t	i;
	t_token	*current;

	current = start;
	if (current->type == HEREDOC && current != start)
		exec_heredoc(current, exec);
	else if (start == head && start->type == PIPE)
		return (0) /*Error : "zsh: parse error near `|'" si le premier charactere est un pipe*/
	while (current->next && current->type != HEREDOC && current->type != PIPE)
		{
			if (current->type == INREDIR)
				exec_inredir(current, exec);
			else if (current->type == OUTREDIR)
				exec_outredir(current, exec);
			else if (current->type == APPEND_MODE)
				exec_append(current, exec);
			else if (current->type == WORD)
				exec_word(current, exec);
			current = current->next;
		}
	}
	return (1);
}

t_exec *exec_init(t_exec *head, t_token current)
{
	t_exec	*exec;
	t_files	*file;

	exec = ft_execnew(current);
	if (exec == NULL)
		return (NULL);
	if (head != 0)
		exec->head = head;
	else
		exec->head = NULL;
	exec->next = NULL;
	exec->type = 0;
	file = ft_filenew();
	cpy_env_from_infos(current->infos, exec);
	return (exec);
}

void	tokens_for_exec(t_token *head_token)
{
	t_token	*current_token;
	t_exec	*head_exec;
	t_exec	*current_exec;
	size_t	i;

	current_token = head_token;
	head_exec = exec_init(0, curent_token);
	if (exec_type(head_exec, current_token, head_token) == 0)
		return (NULL);

	




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
}
