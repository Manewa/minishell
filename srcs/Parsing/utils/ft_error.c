# include "../../../includes/minishell.h"

void ft_lstenvfree(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->value)
			free(env->value);
		if (env->key)
			free(env->key);
		free(env);
		env = tmp; 
	}
}

void	*ft_free_infos(t_infos *infos, char *error, int exit_prg)
{
	if (exit_prg == 1 && infos->line)
		free(infos->line);
	if (infos->env && exit_prg == 1)
		ft_lstenvfree(infos->env);
	if (exit_prg == 1)
		free(infos);
	if (error)
		ft_putstr_fd(error, 2);
	if (exit_prg == 1 && infos->pouexit == POUET)
		exit (0);
	else if (exit_prg == 1 && infos->pouexit != POUET)
		exit (1);
	return (NULL);
}

void *ft_free_token(t_token *token)
{
	t_token *tmp;

	while (token)
	{
		tmp = token->next;
		if (token->line_wip)
			free(token->line_wip);
		free(token);
		token = tmp;
	}
	return (NULL);
}

void *ft_free_infoken(t_infos *infos, t_token *token, char *error, int exit_prg)
{
	if (token)
		ft_free_token(token);
	if (infos)
		ft_free_infos(infos, error, exit_prg);
	return (NULL);
}

void *ft_error_parsing(t_infos *infos, t_token *token, char c)
{
	ft_putstr_fd("pouetsh : syntax error near unexpected token '", 2);
	write (2, &c, 1);
	write (2, "'\n", 2);
	ft_free_infoken(infos, token, 0, 0);
	return (NULL);
}
