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

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->next = NULL;
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
