# include "../../../includes/minishell.h"

int quotes_count(char *str)
{
	int		quotes;
	size_t	i;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == 39)
			quotes += 1;
		i++;
	}
	return (quotes);
}

char *quotes_remover(char *str, int *first, int second)
{
	int		i;
	int		j;
	char	*new_line;

	new_line = malloc((ft_strlen(str) - 1) * sizeof(char));
	if (!new_line)
		return (NULL);
	i = 0;
	j = 0;
	while (i < *first)
		new_line[j++] = str[i++];
	(*first)++;
	while (*first < second)
		new_line[j++] = str[(*first)++];
	while (str[++second])
	{
		new_line[j++] = str[second];
	}
	new_line[j] = '\0';
	*first -= 1;
	free(str);
	return (new_line);
}

void	quotes_detecter(t_exec *current)
{
	int	i;
	int	first;
	int	second;

	i = 0;
	while (current && current->cmd_array && current->cmd_array[i])
	{
		first = 0;
		while (current->cmd_array[i][first])
		{
			if (current->cmd_array[i][first] == '"')
			{
				second = first;
				out_of_dquote(current->cmd_array[i], &second);
				current->cmd_array[i] = quotes_remover(current->cmd_array[i],
						&first, second);
			}
			else if (current->cmd_array[i][first] == 39)
			{
				second = first;
				out_of_squote(current->cmd_array[i], &second);
				current->cmd_array[i] = quotes_remover(current->cmd_array[i],
						&first, second);
			}
			else
				first++;
		}
		i++;
	}
}
