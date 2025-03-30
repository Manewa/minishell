/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_off_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:30:27 by namalier          #+#    #+#             */
/*   Updated: 2025/03/30 12:47:39 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	skip_quotes(char *s, int *i)
{
	char	quote;

	quote = s[*i];
	(*i)++;
	while (s[*i] && s[*i] != quote)
		(*i)++;
}

int	ft_count_word_quote(char *s)
{
	int	count;
	int	i;
	int	start;
	int	double_quote;

	count = 0;
	i = 0;
	double_quote = 0;
	while (s && s[i])
	{
		if (check_first_quote(s, &i, &double_quote) == 1)
			break ;
		else
			count += count_word_n_quotes(s, &i, &double_quote, &start);
	}
	return (count);
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
		str[j++] = s[ib++];
	str[j] = '\0';
	return (str);
}

static void	*ft_free(char **str, char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	(void)c;
	count = ft_count_word_quote(s);
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
	int		count_word;

	i = 0;
	j = 0;
	count_word = ft_count_word_quote(s);
	str = malloc(count_word * sizeof(char *));
	if (!str)
		return (NULL);
	while ((int)j < count_word)
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
