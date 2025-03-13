/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <aibonade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:32:24 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/13 12:57:43 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(t_exec *exec, int fd_pipe[2])
{
	(void)fd_pipe;
	int	i;

	if (exec == exec->head && exec->next == NULL)
	{
		i = 0;

		
		//checker nb arg, si trop $? = 1 ; si aucun on va à ~  et $? = 0
		//si cd "" => rien ne se passe et $? = 0
		//si cd "nom" et nom n'est pas un dossier ou n'existe pas alors $? = 1 et errno affiché
		//si cd "dossier" et dossier non accessible (permission) alors $? = 1 et errno affiché
		;
	}
//	ft_clean_end_builtin(exec, fd_pipe[2]);
}
