# include "../../../includes/minishell.h"

void	ft_free_infos(t_infos *infos)
{
	free(infos->line);
//	ft_free_doubletab(infos->env);
	free(infos);
	exit (2);
}
