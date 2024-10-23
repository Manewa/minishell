int	token_type(t_infos *infos, int i)
{
	char c;

	c = infos->line[i];
	if (c == ' ')
		return (SPACE);
	else if (c == 34)
		return (DOUBLE_QUOTE);
	else if (c = "'")
		return (SINGLE_QUOTE);
	else if (c == '>')
	{
		if (infos->line[i + 1] == '>')
			return (APPEND_MODE);
		return (OUTREDIR);
	}
	else if (c == '<')
	{
		if (infos->line[i + 1] == '<')
			return (HEREDOC);
		return (INREDIR);
	}
	else if (c == '|')
		return (PIPE);
	else
		return (WORD);
}

t_token	tokenization(t_infos *infos)
{
	t_token	token;
	int	type;
	size_t	i;

	i = 0;
	token = ft_lstnew;
	while (infos->line[i])
	{
		type = token_type(infos, i);
		if (type == SPACE)
			token_space(infos, &token, &i);
		else if (type == DOUBLE_QUOTE)
			token_doublequote(infos, &token, &i);
		else if (type == SINGLE_QUOTE)
			token_singlequote(infos, &token, &i);
		else if (type == HEREDOC)
			token_heredoc(infos, &token, &i);
		else if (token_type(infos, i) == OUTREDIR)
			token_outredir(infos, &token, &i);
		else if (type == INREDIR)
			token_inredir(infos, &token, &i);
		else if (type == APPEND_MODE)
			token_append_mode(infos, &token, &i);
		else if (type == PIPE)
			token_pipe(infos, &token);
		else
			token_word(infos, &i, &token);
		i++;
	}
	return (token);
}
