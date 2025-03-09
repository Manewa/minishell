/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:43:47 by namalier          #+#    #+#             */
/*   Updated: 2025/03/07 09:26:57 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/* Si jamais on a un pipe qui suit un autre pipe, il faut renvoyer une erreur et renvoyer au prompt*/
/* Changer le heredoc qui est considere comme un delimiter par uniquement le pipe*/

typedef struct s_infos
{
	int				exit_val;
	char			*line; // A free avant token_to_exec
	struct s_env	*env;
	int				pouexit;
}					t_infos;

typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*value;
	char			*key;
}						t_env;

typedef struct s_token // A free une fois exec envoye
{
	struct s_token	*head;
	struct s_token	*prev;
	struct s_token	*next;
	int				type;
	char			*line_wip;
	int				quotes;
	t_infos			*infos;
}					t_token;

typedef struct s_filesdata
{
	int		rights;//A virer ?
	int		heredoc;
	int		opening_failure;
	int		fd;
	char	*name;
}				t_fdata;

typedef struct s_files
{
	t_fdata	*infile;
	t_fdata	*outfile;
}				t_files;

typedef struct s_lim
{
	struct s_lim	*next;
	char			*limit;
	int				quotes;
	char			*h_name;
}				t_lim;

typedef struct s_exec
{
	struct s_exec	*head;
	struct s_exec	*prev;
	struct s_exec	*next;
	struct s_infos	*infos;
	t_files			*files;
	int				builtin;
	int				is_heredoc;
	struct s_lim	*limiter;
	char			**path;
	char			**env;
	char			**cmd_array;
	char			*cmd_path;
}				t_exec;


#endif

