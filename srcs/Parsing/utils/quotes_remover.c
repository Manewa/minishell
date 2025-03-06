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

// char *quotes_remover(char *str)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*new_line;

// 	new_line = malloc((ft_strlen(str) - quotes_count(str) + 1) * sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '"' || str[i] == 39)
// 			i++;
// 		else
// 			new_line[j++] = str[i++];
// 	}
// 	new_line[j] = '\0';
// 	free(str);
// 	return (new_line);
// }

// void	quotes_detecter(t_token *current)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	while (current->token_line[i])
// 	{
// 		j = 0;
// 		while (current->token_line[i][j])
// 		{
// 			if (current->token_line[i][j] == '"'
// 					|| current->token_line[i][j] == 39)
// 				current->token_line[i] = quotes_remover(current->token_line[i]);
// 			j++;
// 		}
// 		i++;
// 	}
// }
