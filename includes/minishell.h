/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:47:04 by namalier          #+#    #+#             */
/*   Updated: 2024/10/18 15:33:43 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "structs.h"
# include "Libft/libft.h"
# include "libs.h"

/************		main 			**********/

int		main(int argc, char **argv, char **envp);

/************		init_prompt		**********/

int		init_prompt(t_infos *infos, char **envp);

/************		env				**********/

int		ft_cpyenv(t_infos *infos, char **envp);

#endif
