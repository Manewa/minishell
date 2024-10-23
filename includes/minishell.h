/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:47:04 by namalier          #+#    #+#             */
/*   Updated: 2024/10/23 18:18:07 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "structs.h"
# include "Libft/libft.h"
# include "libs.h"

#define	PIPE			1
#define DOUBLE_QUOTE	2
#define INREDIR			3
#define OUTREDIR		4
#define HEREDOC			5
#define WORD			6
#define SINGLE_QUOTE	7
#define APPEND_MODE		8
#define SPACE			9

/************		main 			**********/

int		main(int argc, char **argv, char **envp);

/************		init_prompt		**********/

int		init_prompt(t_infos *infos, char **envp);

/************		env				**********/

int		ft_cpyenv(t_infos *infos, char **envp);

#endif
