/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:43:47 by namalier          #+#    #+#             */
/*   Updated: 2025/01/23 18:34:27 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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
	void	*head;
	void	*prev;
	void	*next;
	int		type;
	int		access;
	char	*full_path;
	char	*line_wip;
	char	**token_line;
	t_infos	**infos;
}					t_token;

/*typedef struct s_filesdata
{
	bool	is_heredoc;
	int		rights;
	char	*name;
}				t_fdata;

typedef struct s_files
{
	s_fdata	*infile_info;
	s_fdata	*outfile_info;
	bool	opening_failure;
}				t_files;

typedef struct s_exec
{
	void	*head;
	void	*prev;
	void	*next;
	int		type;
	t_files	*files_info;
	bool	builtin;
	char	*path;
	char	**cmd_array;
}				t_exec;

*/
#endif

