char *dup_file(char *line, int i)
{
	size_t	j;

	j = 0;
	while (line[i] && line[i] != ' ')
	{
		
	}
}

void exec_inredir(t_token *current, t_exec *exec)
{
	size_t	i;

	i = 1;
	while (current->line_wip[i] && current->line_wip[i] == ' ')
		i++;
	while (current->line_wip[i])
		exec->files_info->infile_info->name = dup_file(current->line_wip, i);

}
