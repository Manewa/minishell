/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:55:57 by namalier          #+#    #+#             */
/*   Updated: 2024/10/29 18:08:35 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_special_char(t_infos *infos, size_t *i)
{
	if (infos->line[*i] == 34 || infos->line[*i] == 39 || infos->line[*i] == '<'
			|| infos->line[*i] == '>' || infos->line[*i] == '|'
			|| infos->line[*i] == ' ')
		return (1);
	return (0);
}
