void exec_inredir(t_token *current, t_exec *exec)
{
	size_t	i;

	i = 0;
	while (current->line_wip[i])
	{
//		exec->files_info->infile_info->name = dup_file(current->line_wip, i);
		exec->files->infile->name[i] = current->line_wip[i];
		i++;
	}
	if (access(exec->files->infile->name, F_OK, R_OK) == 0)
		exec->files->infile->rights = 1100;
	else
		exec->files->opening failure = 1;
}
