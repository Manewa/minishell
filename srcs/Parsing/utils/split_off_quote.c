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

void skip_quotes(char *s, int *i)
{
    char quote;

	quote = s[*i];
    (*i)++;
    while (s[*i] && s[*i] != quote)
        (*i)++;
}

int	ft_count_word_quote(char *s)//, char c)
{
int count;
int i;
int	start;

count = 0;
i = 0;
while (s[i]) 
{	
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	if (!s[i])
		break;
	if (s[i] == '"' || s[i] == 39)
	{
		start = i;
		skip_quotes(s, &i);
		if (i > start + 1)
			count++;
	}
	else 
	{
		count++;
		while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '"' && s[i] != 39)
			i++;
	}
}
return count;
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
	count = ft_count_word_quote(s);//, c);
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
	if (!s)
		return (NULL);
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
