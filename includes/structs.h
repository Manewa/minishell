/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:43:47 by namalier          #+#    #+#             */
/*   Updated: 2025/02/11 18:18:36 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/* Si jamais on a un pipe qui suit un autre pipe, il faut renvoyer une erreur et renvoyer au prompt*/
/* Changer le heredoc qui est considere comme un delimiter par uniquement le pipe*/

typedef struct s_infos
{
	int			s_in;
	int			s_out;
	char		*line;
	char		**env;
	char		**path;
}					t_infos;

typedef struct s_token
{
	struct s_token	*head;
	struct s_token	*prev;
	struct s_token	*next;
	int				type;
	int				access;
	char			*full_path;
	char			*line_wip;
	char			**token_line;
	int				quotes;
	t_infos			*infos;
}					t_token;

typedef struct s_filesdata
{
	int		rights;
	int		heredoc;
	int		opening_failure;
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
	char			*lim;
	int				quotes;
}				t_lim;

typedef struct s_exec
{
	struct s_exec	*head;
	struct s_exec	*prev;
	struct s_exec	*next;
	t_files			*files;
	int				builtin;
	int				is_heredoc;
	int				is_limiter;
	struct s_lim	*limiter;
	char			**path;
	char			**envbis;
	char			**cmd_array;
}				t_exec;


#endif

