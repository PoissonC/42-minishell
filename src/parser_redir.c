/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:31:45 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/17 22:58:24 by yu               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	get_size(t_minishell *m, int idx, t_token *now)
{
	int		ct;
	t_token	*tmp;

	tmp = now;
	ct = 0;
	while (now)
	{
		if (now->type == TYPE_PIPE)
			break ;
		if (now->type >= 1 && now->type <= 3)
			ct++;
		now = now->next;
	}
	m->exe[idx].rdr_size = ct;
	ct = 0;
	now = tmp;
	while (now)
	{
		if (now->type == TYPE_PIPE)
			break ;
		if (now->type == TYPE_HEREDOC)
			ct++;
		now = now->next;
	}
	m->exe[idx].hdc_size = ct;
}

static void	fill_hdc(t_minishell *m, int idx, t_token *now)
{
	int	i;

	i = 0;
	while (i < m->exe[idx].hdc_size)
	{
		if (now->type == TYPE_FD)
		{
			if (now->next->type == TYPE_HEREDOC)
			{
				m->exe[idx].hdc[i].fd = ft_atoi(now->cont);
				now = now->next->next;
				m->exe[idx].hdc[i++].eof = now->cont;
				i++;
			}
		}
		else if (now->type == TYPE_HEREDOC)
		{
			m->exe[idx].hdc[i].fd = 0;
			now = now->next;
			m->exe[idx].hdc[i++].eof = now->cont;
		}
		now = now->next;
	}
}

static void	fill_rdr(t_minishell *m, int idx, t_token *now)
{
	int	i;

	i = 0;
	while (i < m->exe[idx].rdr_size)
	{
		if (now->type == TYPE_FD)
		{
			if (now->next->type != TYPE_HEREDOC)
			{
				fill_rdr_fd(&(m->exe[idx]), i++, now, now->next->next);
				now = now->next->next;
			}
		}
		else if (now->type >= 1 && now->type <= 3)
		{
			fill_rdr_nfd(&(m->exe[idx]), i++, now, now->next);
			now = now->next;
		}
		now = now->next;
	}
}

bool	parse_redir(t_minishell *m)
{
	int		i;
	t_token	*now;

	now = m->t_head->next;
	i = 0;
	while (i < m->exe_size && now)
	{
		get_size(m, i, now);
		if (rdr_malloc(m, i))
			return (1);
		fill_rdr(m, i, now);
		fill_hdc(m, i, now);
		i++;
		now = next_pipe(now);
	}
	return (0);
}
