/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:57:36 by namalier          #+#    #+#             */
/*   Updated: 2024/12/05 17:35:51 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *expander(char *part_of_line)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	while (part_of_line[i])
	{
		if (part_of_line[i] == 39)
			out_of_squote(part_of_line, &readed);
		if (part_of_line[i] == '$')
		{
			while (
		}
	}
}
