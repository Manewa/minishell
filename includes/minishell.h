/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:47:04 by namalier          #+#    #+#             */
/*   Updated: 2025/01/24 15:42:17 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "structs.h"
# include "Libft/libft.h"
# include "libs.h"

#define NON					0
#define OUI					1
#define	PIPE				13
#define DOUBLE_QUOTE		2
#define INREDIR				3
#define OUTREDIR			4
#define HEREDOC				5
#define WORD				6
#define SINGLE_QUOTE		7
#define APPEND_MODE			8
#define SPACES				9
#define	ERROR_PARSING		10
#define QUOTE_NOT_CLOSED	11
#define	NO_PATH				12
#define	NO_ACCESS			15
#define	ACCESS				16
#define	NO_WRITE			14

/************		main 			**********/

int		main(int argc, char **argv, char **envp);

/************		init_prompt		**********/

int		init_prompt(t_infos *infos, char **envp);

/************		env				**********/

void 	ft_cpypath(t_infos *infos);
int		ft_cpyenv(t_infos *infos, char **envp);

/************	token/tokenization	**********/

int		token_type(char *line, int readed, int start, char sep);
t_token	*init_token(t_infos *infos, t_token *head);
t_token	*create_token(t_infos *infos, int *readed, int *start);
t_token	*tokenization(t_infos *infos);

/************	token/token_quotes	***********/

int		out_of_dquote(char *line, int *readed);
int		out_of_squote(char *line, int *readed);
//void	token_doublequote(t_infos *infos, size_t *i, t_token *token);

/************	token/token_line	***********/

char	**parse_word(char *line, int *readed, int start, t_token *token);
void	token_line_wip(t_token *token, char *line, int *readed, int *start);

/***********		expand			***********/

char	*check_name(char *value, char *to_expand);
char	*expand_to_env(char *line, t_infos *infos, char *to_expand, char **env);
char	*expanded_new_line(char *old_line, int start, int end, char *expand);
char	*substitute_expand(char *line, t_infos *infos, int exp);
char	*expand_main(char *line, t_infos *infos);

/************		utils_lst		***********/

void	ft_tokenadd_back(t_token **lst, t_token *new);
t_token	*ft_tokenlast(t_token *lst);
t_token	*ft_tokennew(t_token *head);

/************		utils_parsing	***********/

int		is_special_char(t_infos *infos, size_t *i);
char	is_separator(char c);
char	*strdup_end(char *line, int *readed, int start);

/***********	utils/split_off_quote	******/

char		**split_off_quote(char *s, char c);

#endif
