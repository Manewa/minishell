/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:10:04 by namalier          #+#    #+#             */
/*   Updated: 2024/10/15 18:15:57 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_cpyenv(s_infos *infos, char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
		i++;
	infos->env = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		infos->env[i] = ft_strdup(env[i]);
		if (!infos->env[i])
			return (NULL);
		i++;
	}
	infos->env[i] = NULL;
	return (1);
}
