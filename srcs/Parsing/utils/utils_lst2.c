#include "../../../includes/minishell.h"

t_exec *ft_execlast(t_exec *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_execadd_back(t_exec **head, t_exec *new)
{
	t_exec	*tmp;

	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return;
	}
	tmp = *head;
	ft_execlast(tmp)->next = new;
}

t_lim	*ft_limnew()
{
	t_lim	*new;

	new = malloc(sizeof(t_lim));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->h_name = 0;
	return (new);
}

t_lim *ft_limlast(t_lim *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_env	*ft_envnew(t_env *prev)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	if (prev != NULL)
		new->prev = prev;
	new->value = 0;
	new->key = 0;
	new->next = NULL;
	return (new);
}

