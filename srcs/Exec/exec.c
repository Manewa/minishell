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
		ft_error_child(lst, fd_pipe, old, 1);//code de sortie à 1 ?
	if (dup2(*old, new) == -1)
		ft_error_child(lst, fd_pipe, old, 1);//code de sortie à 1 ?
	if (ft_close(old, lst, fd_pipe) == -1)
		ft_error_child(lst, fd_pipe, old, 1);//code de sortie à 1 ?
}

static void	ft_check_access(t_exec *exec, int fd_pipe[2])
{
	int	i;
	struct stat	f_infos;

	i = 0;
	while (exec->cmd_path[i] && exec->cmd_path[i] != '/')
		i++;
	if (!exec->cmd_path[i])//Si pas de / on consid-re que c'est une cmd sinon un fichier ou un dossier
	{
		if (stat(exec->cmd_path, &f_infos) == -1 || S_ISDIR(f_infos.st_mode))//!exec->cmd_path[i] &&
		{
			ft_putstr_fd(exec->cmd_array[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			ft_error_child(exec, fd_pipe, &(exec->files->outfile->fd), ERROR_NF);//ERR_NF code de sortie à 127
		}
	}
	if (stat(exec->cmd_path, &f_infos) == -1)//si le fichier n'existe pas, il le dit
		ft_error_child(exec, fd_pipe, &(exec->files->outfile->fd), 127);//code de sortie à 127
	if (exec->cmd_path && !S_ISDIR(f_infos.st_mode))
	{
		if (access(exec->cmd_path, X_OK))
		{
			ft_putstr_fd("minipouet: ", 2);
			errno = EACCES;
			ft_error_child(exec, fd_pipe, &(exec->files->outfile->fd), 126);//code de sortie à 126
		}
	}
	else
	{
		ft_putstr_fd("minipouet: ", 2);
		errno = EISDIR;
		ft_error_child(exec, fd_pipe, &(exec->files->outfile->fd), 126);//code de sortie à 126
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
			ft_error_child(one, fd_pipe, NULL, 1);//code de sortie à 1
	}
	ft_open_outfile(fd_pipe, one, one->files->outfile);//ouvrir l'outfile si besoin et éventuellement fermer l'écriture du pipe[1]
	if (one->next != NULL)
		ft_dup2(&(one->files->outfile->fd), STDOUT_FILENO, fd_pipe, one->head);
	if (one->cmd_array && one->cmd_array[0])
	{
		if (exec->builtin)
		{
			//checker les acces des in et outfiles (faire des tests selon le builtin)
			;//ft_builtin();
		}
		ft_check_access(one, fd_pipe);
		execve(one->cmd_path, one->cmd_array, one->env);
		ft_error_child(one, fd_pipe, &(one->files->outfile->fd), 1);//code de sortie à 1 ? 128 ?
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
	while (now)
	{
		if (now->is_heredoc)
			ft_set_heredoc(now, now->limiter, now->files->infile, fd_pipe);
		if ((now->next != NULL) && (pipe(fd_pipe) == -1))
			return(ft_error_exec("minipouet", ERROR_PIPE, now, fd_pipe));
		id = fork();
		if (id == -1)
			return(ft_error_exec("minipouet", ERROR_FORK, now, fd_pipe));
		if (id == 0)
			ft_child(fd_pipe, now);//TO DO + gestion des builtin
		if (now != now->head)
		{
			if (ft_close(&(now->files->infile->fd), now, fd_pipe) == -1)
				return(ft_error_exec("minipouet", ERROR_CLOSE, now, fd_pipe));
		}
		if (now->next != NULL)
		{
			if (ft_close(&fd_pipe[1], now, fd_pipe) == -1)
				return(ft_error_exec("minipouet", ERROR_CLOSE, now, fd_pipe));
			now->next->files->infile->fd = fd_pipe[0];
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
	if (exec_ret > ERROR_EXEC)
	{
		waitpid(last, &last_status, 0);
		if(WIFEXITED(last_status))
			lst->infos->exit_val = WEXITSTATUS(last_status);
		else if(WIFSIGNALED(last_status))
		{
			lst->infos->exit_val = 128 + WTERMSIG(last_status);//checker avec Nathan
		}
	}
	while (wait(NULL) > 0)
		;
	ft_clean_end_exec(lst);
	if(exec_ret <= ERROR_EXEC)
	{
		lst->infos->exit_val = 1;//maj de infos->exit > 0//REVOIR : return value entre 0 & 255 (si en dehors => 255)
		return (ERROR_EXEC);
	}
	return (0);
}
