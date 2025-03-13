/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:57:36 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/13 12:10:15 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

size_t	ft_safe_strlen(const char *c)
{
	size_t	i;

	if (!c)
		return (0);
	i = 0;
	while (c[i])
		i++;
	return (i);
}

void print_keynvalue(t_fdata *outfile, t_env *env)
{
	write(outfile->fd, &tmp->key, ft_safe_strlen(tmp->key));
	write(outfile->fd, "=", 1);
	write(outfile->fd, &tmp->value, ft_safe_strlen(tmp->key));
	if (env->next != NULL)
		write(outfile->fd, "\n", 1);
}

int	ft_env(t_infos *infos, t_fdata *outfile)
{
	t_env	*tmp;

	tmp = infos->env;
	if (exec->cmd_array[1])
	{
		ft_putstr_fd("pouetsh: env: too many arguments", 2);
		infos->exit_val = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	while (tmp)
	{
		if (tmp->key)
		{
			write (outfile->fd, &tmp->key, ft_safe_strlen(tmp->key));
			write (outfile->fd, '=', 1);
			write (outfile->fd, &tmp->value, ft_safe_strlen(tmp->key));
		}
	}
}
