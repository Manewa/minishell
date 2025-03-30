/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:50:05 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/30 14:50:24 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_token	*add_new_node(t_infos *infos, t_token *token_head)
{
	t_token	*token_new;

	token_new = init_token(infos, token_head);
	if (!token_new)
		return (NULL);
	token_new->prev = ft_tokenlast(token_head);
	ft_tokenadd_back(&token_head, token_new);
	return (token_new);
}
