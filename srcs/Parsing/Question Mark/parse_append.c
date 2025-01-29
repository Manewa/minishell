void	parse_append(t_token *current, size_t i)
{
	while (current->line_wip[i] && is_separator(current->line_wip[i] != 0))
		i++;
	if (!current->line_wip[i])
		return (NULL);
	current->token_line = split_off_quote(&i(current->line_wip[i]), ' ');
	quotes_detecter(current);
}
