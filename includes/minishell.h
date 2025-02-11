/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:47:04 by namalier          #+#    #+#             */
/*   Updated: 2025/02/11 18:47:45 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "structs.h"
# include "Libft/libft.h"
# include "libs.h"

#define NO					0
#define YES					1
#define DOUBLE_QUOTE		2
#define INREDIR				3
#define OUTREDIR			4
#define HEREDOC				5
#define WORD				6
#define SINGLE_QUOTE		7
#define APPEND_MODE			8
#define	ERROR_PARSING		10
#define QUOTE_NOT_CLOSED	11
#define	NO_PATH				12
#define	PIPE				13
#define	ECHO				14
#define	CD					15
#define PWD					16
#define	EXPORT				17
#define UNSET				18
#define	ENV					19
#define EXIT				20
#define DOUBLE_PIPE			21
#define	NO_INFO				22
#define	FILE_DOES_NOT_EXIST	23
#define	PERMISSION_DENIED	24

/************		main 			**********/

int		main(int argc, char **argv, char **envp);

/************		init_prompt		**********/

int		init_prompt(t_infos *infos, char **envp);

/************		env/env				**********/

void 	ft_cpypath(t_infos *infos, t_exec *exec);
int		ft_cpyenv(t_infos *infos, char **envp);
int		cpy_env_from_infos(t_infos *infos, t_exec *exec);

/************	tokenization/tokenization	**********/

int		token_type(char *line, int readed, int start, char sep);
t_token	*init_token(t_infos *infos, t_token *head);
t_token	*create_token(t_infos *infos, int *readed, int *start);
t_token	*tokenization(t_infos *infos);

/************	token/token_line	         ***********/

void    ft_cpytoken(t_token *token, char *line,  int start, int readed);
int		line_heredoc(char *line, int *start, int *readed, t_token *token);
void	token_line_wip(t_token *token, char *line, int *readed, int *start);

/***********	tokenization/expand	    ***********/

char	*check_name(char *value, char *to_expand);
char	*expand_to_env(char *line, t_infos *infos, char *to_expand, char **env);
char	*expanded_new_line(char *old_line, int start, int end, char *expand);
char	*substitute_expand(char *line, t_infos *infos, int exp);
char	*expand_main(char *line, t_infos *infos);

/***********       tokenization/tokens_for_exec **********/

int     exec_type(t_exec *exec, t_token **current, t_token *head);
t_exec  *exec_init(t_exec *head, t_token *current);
t_exec	*tokens_for_exec(t_token *head_token);

/***********        exec_type   ***********/

void    exec_append(t_token *current, t_exec *exec);
void    exec_heredoc(t_token *current, t_exec *exec);
void    exec_inredir(t_token *current, t_exec *exec);
void    exec_outredir(t_token *current, t_exec *exec);
char	*ft_pathcmd(char *argv, char *path);
void	find_pathcmd(char **path, t_exec *exec);
void    exec_word(t_token *current, t_exec *exec);


/************	utils/utils_lst	    	    ***********/

t_token	*ft_tokenlast(t_token *lst);
void	ft_tokenadd_back(t_token **lst, t_token *new);
t_exec  *ft_execnew(t_exec *prev);
t_token	*ft_tokennew(t_token *head);
t_files	*ft_filenew(void);

/************	utils/utils_lst2		*************/

void	ft_execadd_back(t_exec **head, t_exec *new);
t_exec	*ft_execlast(t_exec *lst);
t_lim	*ft_limnew(void);
t_lim	*ft_limlast(t_lim *lst);

/************	utils_parsing	***********/

void	out_of_heredoc(char *line, int *i);
int		is_special_char(t_infos *infos, size_t *i);
char	is_separator(char c);
char	*strdup_end(char *line, int *readed, int start);

/***********	utils/split_off_quote	******/

char		**split_off_quote(char *s, char c);

/***********    utils/ft_error      ***********/

void	ft_free_infos(t_infos *infos);

/************   utils/quotes_remover   **********/

int     quotes_count(char *str);
char    *quotes_remover(char *str);
void    quotes_detecter(t_token *token);

/************	utils/quotes	            ***********/

int		out_of_dquote(char *line, int *readed);
int		out_of_squote(char *line, int *readed);
//void	token_doublequote(t_infos *infos, size_t *i, t_token *token);

#endif
