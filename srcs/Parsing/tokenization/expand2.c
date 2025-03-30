/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:23:21 by namalier          #+#    #+#             */
/*   Updated: 2025/03/30 17:23:49 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	cpy_part_line(char *old, char *expand, int start, char *new)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	j = 0;
	get_out_of_rules(old, &i);
	while (k < i)
	{
		new[k] = old[k];
		k++;
	}
	while (i < start && old[i] != '$')
	{
		new[i] = old[i];
		i++;
	}
	while (expand && expand[j])
		new[i++] = expand[j++];
	return (i);
}
