/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibonade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:30:52 by aibonade          #+#    #+#             */
/*   Updated: 2025/03/07 09:35:50 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_dup2(int *old, int new, int fd_pipe[], t_exec *lst)
{
	int	tmp;

	tmp = new;
	if (ft_close(&tmp, lst, fd_pipe) == -1)
		ft_error_child(lst->head, fd_pipe, old, NULL);
	if (dup2(*old, new) == -1)
		ft_error_child(lst->head, fd_pipe, old, NULL);
	if (ft_close(old, lst, fd_pipe) == -1)
		ft_error_child(lst->head, fd_pipe, old, NULL);
}

static void	ft_check_access(t_exec *exec, int fd_pipe[2])
{
	int	i;

	if (exec->cmd_path)
	{
		i = 0;
		while (exec->cmd_path[i] && exec->cmd_path[i] != '/')
			i++;
		if (!exec->cmd_path[i] && access(exec->cmd_path, F_OK | X_OK))
		{
			ft_putstr_fd(exec->cmd_array[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			ft_error_child(exec->head, fd_pipe, &(exec->files->outfile->fd), "");
		}
	}
}

static void	ft_child(int fd_pipe[2], t_exec *one)//ici on exit si error
{
	/*TO DO
	  - Gestion des builtin (/!\ cd export (!!) & unset ne sont pas utilisables en milieu de pipe)
	  - Ajout des éléments pour les signaux
	  */
	ft_open_infile(fd_pipe, one, one->limiter, one->files->infile);//ouvrir l'infile si besoin et eventuellement fermer la lecture du pipe-1[0]
	if (one != one->head || one->files->infile->heredoc != NO_INFO)
		ft_dup2(&(one->files->infile->fd), STDIN_FILENO, fd_pipe, one->head);
	if (one->next != NULL)//Si pas le dernier on ferme la lecture du nouveau pipe
	{
		if (ft_close(&fd_pipe[0], one, fd_pipe) == -1)
			ft_error_child(one->head, fd_pipe, NULL, NULL);//exit(ERROR_EXEC);//ERROR
	}
	ft_open_outfile(fd_pipe, one, one->files->outfile);//ouvrir l'outfile si besoin et éventuellement fermer l'écriture du pipe[1]
	if (one->next != NULL)
		ft_dup2(&(one->files->outfile->fd), STDOUT_FILENO, fd_pipe, one->head);
	if (one->cmd_array && one->cmd_array[0])//ici
	{
		ft_check_access(one, fd_pipe);//A adapter => récupérer et afficher errno
		execve(one->cmd_path, one->cmd_array, one->env);
		ft_error_child(one->head, fd_pipe, &(one->files->outfile->fd), NULL);//est-ce qu'on ferme bien tout (là on ferme les deux entrées et sorties std autre que erreur)
	}
	else
		ft_clean_end_exec(one->head);
	exit(0);
}

static int	ft_exec(t_exec *lst, pid_t *last)
{
	int		fd_pipe[2];
	pid_t	id;
	t_exec	*now;

	now = lst->head;
	fd_pipe[0] = -1;
	fd_pipe[1] = -1;
	while (now)//on entre sur la premiere et des quon est a null on s'arrete
	{
		if (now->is_heredoc)
			ft_set_heredoc(now, now->limiter, now->files->infile, fd_pipe);//fermer les pipe si erreur
		if ((now->next != NULL) && (pipe(fd_pipe) == -1))
			return(ft_error_exec("minipouet", ERROR_PIPE, now, fd_pipe));//return (ERROR_PIPE);
		id = fork();
		if (id == -1)
			return(ft_error_exec("minipouet", ERROR_FORK, now, fd_pipe));//return (ERROR_FORK);
		if (id == 0)
			ft_child(fd_pipe, now);//TO DO + gestion des builtin
		if (now != now->head)//si on n'est pas sur la tete on ferme la lecture du pipe précédent
		{
			if (ft_close(&(now->files->infile->fd), now, fd_pipe) == -1)
				return(ft_error_exec("minipouet", ERROR_CLOSE, now, fd_pipe));//return (ERROR_CLOSE);
		}
		if (now->next != NULL)
		{
			if (ft_close(&fd_pipe[1], now, fd_pipe) == -1)
				return(ft_error_exec("minipouet", ERROR_CLOSE, now, fd_pipe));//return (ERROR_CLOSE);//ERROR
			now->next->files->infile->fd = fd_pipe[0];//la lecture
		}
		now = now->next;
		*last = id;
	}
	return (0);
}

int	ft_main_exec(t_exec *lst)//debut de l'exec avec récupération de la liste de token + retourner valeur de retour
{
	int		exec_ret;
	pid_t	last;
	int		last_status;

	errno = 0;//ajoute
	exec_ret = ft_exec(lst, &last);
	if (exec_ret > ERROR_EXEC)//!= ERROR_EXEC)
	{
		waitpid(last, &last_status, 0);
		if(WIFEXITED(last_status))//Maj de infos avec la sortie du dernier
		{
			;//WEXITSTATUS(status)
		}
		else if(WIFSIGNALED(last_status))//Maj de infos avec la sortie du dernier
		{
			;//WTERMSIG(status)
		}
	}
	while (wait(NULL) > 0)
		;
	ft_clean_end_exec(lst);
	if(exec_ret <= ERROR_EXEC)//== ERROR_EXEC)
	{
		//maj de infos->exit value ? si oui : > 0
		return (ERROR_EXEC);//REVOIR : return value entre 0 & 255 (si en dehors => 255)
	}
	return (0);
}
