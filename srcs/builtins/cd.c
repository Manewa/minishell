/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <aibonade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:32:24 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/15 20:35:29 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int ft_nb_args_cd(t_exec *exec, int fd_pipe[2], int child, int std_fd)
{
	int	i;

	i = 0;
	while (exec->cmd_array[i])
		i++;
	if (i != 2)//checker nb arg, si trop $? = 1 ;
	{
		if (std_fd == 1 || std_fd == 3)//jouer avec les param de clean end builtin si on doit virer ces 4 lignes
			exec->files->infile->fd = -1;
		if (std_fd == 2 || std_fd == 3)
			exec->files->outfile->fd = -1;
		if (i > 2)
		{
			ft_putstr_fd("minipouet: ", 2);
			ft_putstr_fd(exec->cmd_array[0], 2);
			ft_putstr_fd(": too many arguments\n", 2);
			return (ft_clean_end_builtin(exec, fd_pipe, 1, child));
		}
		else
			return (ft_clean_end_builtin(exec, fd_pipe, 0, child));
	}
	return (i);
}

static int ft_set_pwd(t_exec *exec)
{
	t_env	*tmp;
	t_env	*node_pwd;

	tmp = exec->infos->env;
	while (tmp && ft_strncmp(tmp->key, "PWD", 4))
		tmp = tmp->next;
	node_pwd = tmp;
	tmp = exec->infos->env;
	while (tmp && ft_strncmp(tmp->key, "OLDPWD", 7))
		tmp = tmp->next;
	if (tmp)
	{
		if (tmp->value)
			free(tmp->value);
		if (node_pwd)
		{
			if (node_pwd->value)
				tmp->value = node_pwd->value;
			else
				tmp->value = NULL;
			node_pwd->value = ft_getcwd();
			if (!node_pwd->value)
				return (1);
		}
		else
			tmp->value = NULL;
	}
	else if (node_pwd)
	{
		node_pwd->value = ft_getcwd();
// printf("pwd->value2 = %s\n", node_pwd->value);
		if (!node_pwd->value)
			return (1);
	}
// printf("old->value = %s\n", tmp->value);
	return (0);
}

int	ft_cd(t_exec *exec, int fd_pipe[2], int child, int std_fd)
{
	int	nb_arg;

	nb_arg = ft_nb_args_cd(exec, fd_pipe, child, std_fd); 
	if (nb_arg != 2)
		return (ft_clean_end_builtin(exec, fd_pipe, nb_arg, child));
	else if (exec->cmd_array[1][0] && chdir(exec->cmd_array[1]) == -1)//si exec->cmd_array[1] = "" ?
	{
		if (std_fd == 1 || std_fd == 3)
			exec->files->infile->fd = -1;
		if (std_fd == 2 || std_fd == 3)
			exec->files->outfile->fd = -1;
		ft_putstr_fd("minipouet: ", 2);
		perror(exec->cmd_array[0]);
		return (ft_clean_end_builtin(exec, fd_pipe, 1, child));
	}
	if (ft_set_pwd(exec))
	{
		ft_putstr_fd("minipouet: ", 2);
		perror(exec->cmd_array[0]);
		return (1);
	}
	return (0);
}
