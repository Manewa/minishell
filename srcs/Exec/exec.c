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

static void	ft_dup2(int old, int new, int fd_pipe[], t_exec *lst)
{
	if (ft_close(new, lst, fd_pipe) == -1)
		ft_error_child(lst->head, fd_pipe);//exit(ERROR_EXEC);//ERROR
	if (dup2(old, new) == -1)
		ft_error_child(lst->head, fd_pipe);//exit(ERROR_EXEC);//gestion d'erreur ft_error_exec("Dup2 error.", data, fd_pipe);
	if (ft_close(old, lst, fd_pipe) == -1)
		ft_error_child(lst->head, fd_pipe);//exit(ERROR_EXEC);//ERROR
}

static void	ft_child(int fd_pipe[2], t_exec *one)//ici on exit si error
{
	/*TO DO
	  - Gestion des builtin (/!\ cd export (!!) & unset ne sont pas utilisables en milieu de pipe)
	  - Ajout des éléments pour les signaux
	  */
//OUVERTS : Infile (fdp-1[0], si one != one->head), fdp[0]*, fdp[1]* (*si one->next != NULL)
	ft_open_infile(fd_pipe, one, one->limiter, one->files->infile);//ouvrir l'infile si besoin et eventuellement fermer la lecture du pipe-1[0]
//OUVERTS : Infile, fdp[0]*, fdp[1]* (*si one->next != NULL)
	if (one != one->head || one->files->infile->heredoc != NO_INFO)
		ft_dup2(one->files->infile->fd, STDIN_FILENO, fd_pipe, one->head);
	if (one->next != NULL)//Si pas le dernier on ferme la lecture du nouveau pipe
	{
		if (ft_close(fd_pipe[0], one, fd_pipe) == -1)//ICI faut fermer infile
			ft_error_child(one->head, fd_pipe);//exit(ERROR_EXEC);//ERROR
	}
//OUVERTS : Infile, fdp[1]* (*si one->next != NULL)
	ft_open_outfile(fd_pipe, one, one->files->outfile);//ouvrir l'outfile si besoin et éventuellement fermer l'écriture du pipe[1]
													   //OUVERTS : Infile, fdp[1]*, outfile (*si one->next != NULL)
	if (one->next != NULL)
		ft_dup2(one->files->outfile->fd, STDOUT_FILENO, fd_pipe, one->head);
	//ft_check_access(cmd, data);//A adapter => récupérer et afficher errno
	if (one->cmd_array && one->cmd_array[0])//ici
	{
		execve(one->cmd_path, one->cmd_array, one->env);
		ft_error_child(one->head, fd_pipe);//exit a gerer ft_error_exec("Execve error.", data, fd_pipe);//check avec Nathan
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
			ft_check_heredoc(now->is_heredoc, now->limiter, now->files->infile);//done (ajouter infos ou env de base quand expand) : on peut mettre env en char ** : a priori unset et export ne fonctionnent pas dans un pipeline (checker si leur position change qqchose ou pas et checker que c'est bon aussi avec les autres builtins (et qu'il n'y a pas de modifications de l'env par des non builtin))+gestion erreurs
		if ((now->next != NULL) && (pipe(fd_pipe) == -1))
			return(ft_error_exec("minipouet", ERROR_PIPE, now, fd_pipe));//return (ERROR_PIPE);
		id = fork();
		if (id == -1)
			return(ft_error_exec("minipouet", ERROR_FORK, now, fd_pipe));//return (ERROR_FORK);
		if (id == 0)
			ft_child(fd_pipe, now);//TO DO + gestion des builtin
		if (now != now->head)//si on n'est pas sur la tete on ferme la lecture du pipe précédent
		{
			if (ft_close(now->files->infile->fd, now, fd_pipe) == -1)
				return(ft_error_exec("minipouet", ERROR_CLOSE, now, fd_pipe));//return (ERROR_CLOSE);
		}
		if (now->next != NULL)
		{
			if (ft_close(fd_pipe[1], now, fd_pipe) == -1)
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
