#include "../../../includes/minishell.h"

t_env *ft_envlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	ft_envlast(tmp)->next = new;
}

void	ft_limadd_back(t_lim **lst, t_lim *new)
{
	t_lim	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	ft_limlast(tmp)->next = new;
}

int ft_infonew(t_infos **infos, char **envp)
{
	t_infos	*new;

	new = malloc(sizeof(t_infos));
	if (!new)
		return (1);
	new->exit_val = 0;
	new->env = ft_cpyenv(envp);
	new->line = 0;
	new->pouexit = POUET;
	*infos = new;
	return (0);
}
