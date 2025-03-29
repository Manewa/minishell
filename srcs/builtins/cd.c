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

static int	ft_nb_args_cd(t_exec *exec, int fd_pipe[2], int child, int std_fd)
{
	int	i;

	i = 0;
	while (exec->cmd_array[i])
		i++;
	if (i != 2)
	{
		if (std_fd == 1 || std_fd == 3)
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

static int	ft_set_pwd(t_exec *exec)
{
	t_env	*oldpwd;
	t_env	*pwd;

	pwd = ft_get_env_value(exec->infos->env, "PWD", 4);
	oldpwd = ft_get_env_value(exec->infos->env, "OLDPWD", 7);
	if (oldpwd)
	{
		if (oldpwd->value)
			free(oldpwd->value);
		if (pwd && pwd->value)
			oldpwd->value = pwd->value;
		else
			oldpwd->value = NULL;
	}
	if (pwd)
	{
		if (!oldpwd && pwd->value)
			free(pwd->value);
		pwd->value = ft_getcwd();
		if (!pwd->value)
			return (1);
	}
	return (0);
}

int	ft_cd_home(t_exec *exec, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp && ft_strcmp(tmp->key, "HOME"))
		tmp = tmp->next;
	if (tmp && tmp->value)
	{
		if (exec->cmd_array[1])
			free(exec->cmd_array[1]);
		if (tmp->value[0])
		{
			exec->cmd_array[1] = tmp->value;
			return (1);
		}
		return (-1);
	}
	ft_putstr_fd("minipouet: cd: HOME not set\n", 2);
	return (0);
}

static int	ft_cd_and_setpwd(t_exec *exec, int home)
{
	if (ft_chdir(exec))
	{
		if (home)
			exec->cmd_array[1] = NULL;
		return (1);
	}
	if (ft_set_pwd(exec))
	{
		if (home)
			exec->cmd_array[1] = NULL;
		ft_putstr_fd("minipouet: ", 2);
		perror(exec->cmd_array[0]);
		return (1);
	}
	return (0);
}

int	ft_cd(t_exec *exec, int fd_pipe[2], int child, int std_fd)
{
	int	nb_arg;
	int	home;

	home = 0;
	nb_arg = ft_nb_args_cd(exec, fd_pipe, child, std_fd);
	if (nb_arg > 2)
		return (1);
	if (!exec->cmd_array[1] || !exec->cmd_array[1][0])
	{
		home = ft_cd_home(exec, exec->infos->env);
		if (!home)
			return (1);
		if (home == -1)
			return (0);
	}
	if (ft_cd_and_setpwd(exec, home))
		return (1);
	if (home)
		exec->cmd_array[1] = NULL;
	return (0);
}
