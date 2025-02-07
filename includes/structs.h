/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:43:47 by namalier          #+#    #+#             */
/*   Updated: 2025/02/04 10:56:17 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/* Si jamais on a un pipe qui suit un autre pipe, il faut renvoyer une erreur et renvoyer au prompt*/

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
	t_infos			*infos;
}					t_token;

typedef struct s_filesdata
{
	int		rights;
	char	*name;
}				t_fdata;

typedef struct s_files
{
	t_fdata	*infile;
	t_fdata	*outfile;
	int		opening_failure;
}				t_files;

typedef struct s_exec
{
	struct s_exec	*head;
	struct s_exec	*prev;
	struct s_exec	*next;
	t_files			*files;
	int				builtin;
	int				is_heredoc;
	char			*delimiter;
	char			**path;
	char			**envbis;
	char			**cmd_array;
}				t_exec;


#endif

