/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_for_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:28:29 by namalier          #+#    #+#             */
/*   Updated: 2025/01/17 16:25:10 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	tokens_for_exec(t_token *lst_token)
{
	t_token	*current;

	current = lst_token;
	while (current->next)
	{
		if (current != lst_token)
			current = current->next;
		if (current->type == WORD)
			parse_word(current);
		else if (current->type == APPEND_MODE)
			parse_append(current);
		else if (current->type == HEREDOC)
			parse_heredoc(current);
		else if (current->type == OUTREDIR)
			parse_outredir(current);
		else if (current->type == INREDIR)
			parse_inredir(current);
		else if (current->type == PIPE)
			parse_PIPE(current);
	}
}
