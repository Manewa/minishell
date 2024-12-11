/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:57:36 by namalier          #+#    #+#             */
/*   Updated: 2024/12/11 16:16:00 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *find_from_env(char *expand, t_infos *infos, int *start)
{
	size_t	end;

	end = *i;
	while (expand[end] && expand[end] != ' '))
	{
		
	}
}


char *expander(char *part_of_line, t_infos *infos)
{
	int		i;
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
