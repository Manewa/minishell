void	ft_cpy_fullpath(t_token *current)
{
	size_t	i;
	
	i = 0;
	free(current->token_line[0]);
	current->token_line[0] = malloc((ft_strlen(current->full_path) + 1)
			*sizeof(char));
	if (!current->token_line[0])
		return (NULL);
	while (current->full_path[i])
		current->token_line[0][i] = current->full_path[i];
	current->token_line[0][i] = '\0';
}

char	*ft_cpy_envpath(char *argv, char *path)
{
	size_t	i;
	size_t	j;
	char	*cpath;

	i = 0;
	j = 0;
	cpath = malloc((ft_strlen(argv) + ft_strlen(path) + 2) * sizeof(char));
	if (!cpath)
		return (NULL);
	while (path[i])
	{
		cpath[i] = path[i];
		i++;
	}
	cpath[i++] = '/';
	while (argv[j])
		cpath[i++] = argv[j++];
	cpath[i] = '\0';
	return (cpath);
}

void	parse_word(t_token *current, size_t i)
{
	current->token_line = split_off_quote(&(current->line_wip[i]), ' ');
	quotes_detecter(current);
	access_cmd(current);
	check_builtins(current);
}
