/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:47:04 by namalier          #+#    #+#             */
/*   Updated: 2024/10/29 18:07:05 by namalier         ###   ########.fr       */
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
#define SPACES			9

/************		main 			**********/

int		main(int argc, char **argv, char **envp);

/************		init_prompt		**********/

int		init_prompt(t_infos *infos, char **envp);

/************		env				**********/

int		ft_cpyenv(t_infos *infos, char **envp);

/************		tokenization	**********/

t_token	*tokenization(t_infos *infos);
t_token	*token_type(t_infos *infos, size_t *i);

/************		token_quotes	***********/

void	token_doublequote(t_infos *infos, size_t *i, t_token *token);

/************		utils_lst		***********/

void	ft_tokenadd_back(t_token **lst, t_token *new);
t_token	*ft_tokenlast(t_token *lst);

/************		utils_parsing	***********/

int		is_special_char(t_infos *infos, size_t *i);

#endif
