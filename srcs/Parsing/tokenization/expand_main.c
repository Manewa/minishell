/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 13:45:32 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/30 13:46:05 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* Substitute expand defines start and end of an the expand
 * to change ($USER for exemple)
 *
 * The expand run until finding anything else than alnum char or '_'
 * Return expand, the line with the expand.
 */

static char	*substitute_expand(char *line, t_infos *inf, int exp, t_token *tok)
{
	int		end;
	size_t	j;
	int		start;
	char	*expand;

	start = exp;
	end = exp;
	j = 0;
	if (line[end] && (ft_isalpha(line[end]) == 1 || line[end] == '_'))
	{
		end++;
		while (line[end] && (ft_isalnum(line[end]) || line[end] == '_'))
			end++;
	}
	expand = malloc((end - start + 1) * sizeof(char));
	if (!expand)
		return (ft_free_infoken(inf, tok, "ERROR : malloc expand", 1));
	while (start < end)
		expand[j++] = line[start++];
	expand[j] = '\0';
	expand = expand_to_env(expand, inf->env);
	if (!expand)
		return (ft_free_infoken(inf, tok, "ERROR : malloc expand", 1));
	expand = expanded_new_line(line, exp - 1, end, expand);
	return (expand);
}

void	get_out_of_rules(char *line, int *i)
{
	int	double_quote;

	double_quote = 0;
	if (line[*i] == '"' && double_quote == 1)
		double_quote = 0;
	else if (line[*i] == '"' && double_quote == 0)
		double_quote = 1;
	if (line[*i] == 39 && double_quote == 0)
		out_of_squote(line, i);
	if (line[*i] == '<' && line[(*i) + 1] == '<' && double_quote == 0)
		out_of_heredoc(line, i);
}

char	*the_right_expand(char *line, int *i, t_infos *infos, t_token *token)
{
	if (line[*i] && line[*i + 1] && line[*i] == '$' && line[*i + 1] != '?')
	{
		if (ft_isalpha(line[*i + 1]) == 1 || line[*i + 1] == '_')
		{
			line = substitute_expand(line, infos, ++(*i), token);
			*i = 0;
		}
		else if (line[*i + 1] && (line[*i + 1] == '"' || line[*i + 1] == 39))
			line = expanded_new_line(line, *i, (*i) + 1, NULL);
		else
			(*i)++;
	}
	else if (line[*i] && line[*i + 1] && line[*i] == '$' && line[*i + 1] == '?')
	{
		line = expanded_new_line(line, *i, *i + 2, ft_itoa(infos->exit_val));
		(*i)++;
	}
	else if (line[*i] && (line[0] != '$' || line[0] != 39 || !line[*i + 1]))
		(*i)++;
	return (line);
}

/* Main expand with rules :
 * line -> line where we search for a '$'
 * infos -> Env (lst) inside
 * 
 * -> check for '$?' with exit_val in infos
 *
 *	While until the end of line and get back to 0 each time we find an expand
 *	to verify that there's no expand in an expand.
 *
 * Return line (with the new expand)
 */

static char	*expand_main(char *line, t_infos *infos, t_token *token)
{
	int		i;

	i = 0;
	while (line && line[i])
	{
		get_out_of_rules(line, &i);
		line = the_right_expand(line, &i, infos, token);
	}
	if (!line)
		return (ft_free_infoken(infos, token, "ERROR : Bug during expand", 1));
	else if (line)
		return (line);
	return (NULL);
}

void	expand_token(t_token *token, t_infos *infos)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->line_wip && tmp->line_wip[0])
			tmp->line_wip = expand_main(tmp->line_wip, infos, token);
		tmp = tmp->next;
	}
}
