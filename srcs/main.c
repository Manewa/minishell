/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:01:29 by namalier          #+#    #+#             */
/*   Updated: 2025/03/28 20:52:40 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_sig = 0;

void	get_readline(t_infos *infos)
{
	infos->line = readline("minipouet> ");
	if (!infos->line)
		ft_free_infos(infos, 0, -1);
	if (g_sig == SIGINT || g_sig == SIGINT_HD)
	{
		infos->exit_val = 130;
		g_sig = 0;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_infos	*infos;
	t_exec	*exec;

	(void)argv;
	if (!isatty(0))
		return (1);
	if (argc != 1 || ft_infonew(&infos, envp))
		return (1);
	while (infos->pouexit)
	{
		exec = NULL;
		set_signal(infos);
		get_readline(infos);
		if (infos->line && infos->line[0] && infos->line[0] != ' ')
			add_history(infos->line);
		if (infos->line && infos->line[0])
			exec = main_parsing(infos);
		if (exec)
			ft_main_exec(exec);
	}
	rl_clear_history();
	return (0);
}
