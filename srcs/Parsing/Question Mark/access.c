
void access_cmd(t_token *current)
{
	size_t	i;

	i = 0;
	while (current->infos->path[i])
	{
		current->full_path = ft_cpy_envpath(current->token_line[0],
				current->infos->path[i]);
		if (!(current->full_path))
			return (NULL);
		if (access(cmd->pathcmd, F_OK | X_OK) == -1)
		{
			free(current->full_path);
			i++;
		}
		else
		{
			ft_cpy_fullpath(current);
			return (current->full_path);
		}
	}
	token->access = NO_PATH;
	return (NULL);
}

void access_write(t_token *current)
{
	size_t	j;

	j = 1;
	while (current->token_line[j])
	{
		if (access(current->token_line[j], F_OK) == -1)
		{
			current->access = NO_ACCESS;
		else
		{
			if (access(current->token_line[j], W_OK) != -1)
				current->type = ACCESS;
			else
				current->type = NO_WRITE;
		}
	}
	j++;
}


