/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:02:06 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/06 17:04:31 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int sig_global;

void sig_handler_c(int signum)
{
	if (signum == SIGINT)
	{
		sig_global = signum;
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*
 * define_signal
 *
 * define what does each signal, redirect to sig_fun(signum) each time a signal is received
 * sigaction is two things :
 * 			1) Struct from signal.h
 * 				sa_handler = function to exec when found a signal
 * 				sa_flags = no flags used in minishell
 * 				sa_mask = blocke signals during exec
 * 			2) function taking sigaction struct as argument
 * 				sigaction (int signum, struct sigaction new, struct sigaction old which is NULL here)
 * 				return 0 if success
 * 				return -1 if failed
 */

int	define_signal(int signum, void (*sig_fun)(int), t_infos *infos)
{
	struct sigaction	sig_a;

	sig_a.sa_handler = sig_fun;
	sig_a.sa_flags = 0;
	sigemptyset(&sig_a.sa_mask);
	if (sigaction(signum, &sig_a, NULL) < 0)
	{
		infos->exit_val = errno;
		perror("sigaction");
		return (-1);
	}
	return (0);
}

/*
 * set_signal
 *
 * set the value and effect of each signal
 * -> ctrl / c = SIGINT means quit
 * -> ctrl / \ = SIGQUIT means quit but SIG_IGN means ignore it
 */

void	set_signal(t_infos *infos)
{
	define_signal(SIGINT, &sig_handler_c, infos);
	define_signal(SIGQUIT, SIG_IGN, infos);
}
