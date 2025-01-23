/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_for_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:28:29 by namalier          #+#    #+#             */
/*   Updated: 2025/01/23 18:40:31 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */





/*void	tokens_for_exec(t_token *lst_token)
{
	t_token	*current;
	size_t	i;

	current = lst_token;
	while (current->next)
	{
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
