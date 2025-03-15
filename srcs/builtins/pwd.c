/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <aibonade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:19:16 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/15 18:19:18 by aibonade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getcwd(void)
{
	char	buffer[1048];

	if (!getcwd(buffer, 1048))
		return (NULL);
	return (ft_strdup(buffer));
}

int		ft_pwd(t_exec *exec)
{
	char	*pwd;

	pwd = ft_getcwd();
	if (!pwd)
	{
		ft_putstr_fd("minipouet: ", 2);
		perror(exec->cmd_array[0]);
		return (1);
	}
	ft_putstr_fd(pwd, exec->files->outfile->fd);
	ft_putstr_fd("\n", exec->files->outfile->fd);
	free(pwd);
	return (0);
}