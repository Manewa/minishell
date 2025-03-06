/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <aibonade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:46:56 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/06 16:18:03 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int ft_len_ul(unsigned long n)
{
	size_t	len;

	len = 0;
	if (!n)
		return (1);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}
static void ft_change_ul(unsigned long n, char *s, size_t i)
{
	s[i] = '\0';
	i--;
	while (n > 9)
	{
		s[i] = n % 10 + 48;
		i--;
		n = n / 10;
	}
	s[i] = n % 10 + 48;
}

char *ft_ultoa(unsigned long n)
{
	char			*str;
	size_t			len;
	unsigned long	nbr;

	nbr = n;
	len = ft_len_ul(n);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_change_ul(nbr, str, len);
	return (str);
}
