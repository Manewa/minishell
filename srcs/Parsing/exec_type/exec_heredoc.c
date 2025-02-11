#include "../../../includes/minishell.h"

t_lim *limiter_init(t_token *token, t_exec *exec)
{
	t_lim *lim;

	lim = ft_limnew();
	if (exec->limiter)
		ft_limlast(exec->limiter)->next = lim;
	lim->next = NULL;
	if (token->quotes == 0)
		lim->quotes = NO;
	else
		lim->quotes = YES;
	lim->lim = ft_strdup(token->line_wip);
	if (!lim->lim)
		return (NULL);
	return (lim);
}

void exec_heredoc(t_token *current, t_exec *exec)
{
	t_lim	*lim;

	exec->is_heredoc += 1;
	lim = limiter_init(current, exec);
	if (exec->files->infile->heredoc == NO_INFO)
		exec->files->infile->heredoc = YES;
}
