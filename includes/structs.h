/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:43:47 by namalier          #+#    #+#             */
/*   Updated: 2024/10/29 15:13:08 by namalier         ###   ########.fr       */
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
}					t_infos;

typedef struct s_token
{
	void	*head;
	void	*prev;
	void	*next;
	int		type;
	char	*word;
	char	**token;
}					t_token;

#endif

