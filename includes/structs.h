/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:43:47 by namalier          #+#    #+#             */
/*   Updated: 2025/01/20 13:15:37 by namalier         ###   ########.fr       */
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

#endif

