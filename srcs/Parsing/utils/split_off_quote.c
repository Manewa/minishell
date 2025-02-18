/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_off_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:30:27 by namalier          #+#    #+#             */
/*   Updated: 2025/02/18 12:20:07 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_count_word_quote(char *s, char c)
{
	int	count_word;
	int	i;

	i = 0;
	count_word = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count_word++;
			while (s[i] && s[i] != c)
			{
				if (s[i] == 39)
					out_of_squote(s, &i);
				else if (s[i] == '"')
					out_of_dquote(s, &i);
				else
					i++;
			}
		}
		if (s[i])
			i++;
	}
	return (count_word);
}

static char	*ft_cpy_str(char *str, char *s, int *i, char c)
{
	size_t	j;
	int		ib;

	j = 0;
	ib = *i;
	while (s[*i] && s[*i] != c)
	{
		if (s[*i] == 39)
			out_of_squote(s, i);
		else if (s[*i] == '"')
			out_of_dquote(s, i);
		else
			(*i)++;
	}
		str = malloc((*i - ib + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (ib < *i)
	{
		str[j] = s[ib];
		j++;
		ib++;
	}
	str[j] = '\0';
	return (str);
}

static void	*ft_free(char **str, char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = ft_count_word_quote(s, c);
	while (i <= count)
	{
		free(str[i]);
		i++;
	}
	return (NULL);
}

char	**split_off_quote(char *s, char c)
{
	int		i;
	size_t	j;
	char	**str;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	str = malloc((ft_count_word_quote(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while ((int)j < ft_count_word_quote(s, c))
	{
		while (s[i] == c)
			i++;
		str[j] = ft_cpy_str(str[j], s, &i, c);
		if (!str[j])
			return (ft_free(str, s, c));
		while (s[i] == c)
			i++;
		j++;
	}
	str[j] = NULL;
	return (str);
}
