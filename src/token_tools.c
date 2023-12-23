/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:54:04 by yu                #+#    #+#             */
/*   Updated: 2023/12/23 16:47:27 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static void	get_s(t_minishell *m, t_sort *s)
{
	int		i;
	t_token	*now;

	s->a_now = m->t_head->next;
	now = m->t_head->next;
	i = 0;
	while (i++ < m->a_size)
		now = now->next;
	s->b_now = now;
	s->idx_a = 0;
	s->idx_b = 0;
}

static void	merge(t_minishell *m, t_sort *s)
{
	if (s->a_now->pos > s->b_now->pos)
	{
		s->idx_b++;
		m->t_tail->next = s->b_now;
		s->b_now = s->b_now->next;
	}
	else
	{
		s->idx_a++;
		m->t_tail->next = s->a_now;
		s->a_now = s->a_now->next;
	}
	m->t_tail = m->t_tail->next;
}

void	sort(t_minishell *m)
{
	t_sort	s;

	get_s(m, &s);
	m->t_tail = m->t_head;
	while (s.idx_a < m->a_size && s.idx_b < m->b_size)
		merge(m, &s);
	if (s.idx_a == m->a_size)
	{
		m->t_tail->next = s.b_now;
		while (s.idx_b++ < m->b_size)
			m->t_tail = m->t_tail->next;
	}
	else
	{
		m->t_tail->next = s.a_now;
		while (s.idx_a++ < m->a_size)
			m->t_tail = m->t_tail->next;
	}
	m->t_tail->next = NULL;
	m->a_size += m->b_size;
	m->b_size = 0;
}

static bool	new_tok(t_minishell *m, int idx)
{
	t_token	*new_tok;

	new_tok = ft_malloc(sizeof(t_token), m->mem);
	if (!new_tok)
		return (1);
	new_tok->next = NULL;
	new_tok->cont = NULL;
	m->t_tail->next = new_tok;
	m->t_tail = new_tok;
	m->b_size++;
	new_tok->cont = ft_malloc(2, m->mem);
	if (!new_tok->cont)
		return (1);
	new_tok->cont[0] = '|';
	new_tok->cont[1] = '\0';
	new_tok->end_pos = -1;
	new_tok->pos = idx;
	new_tok->type = TYPE_PIPE;
	new_tok->is_div = 0;
	return (0);
}

bool	pipeline(t_minishell *m)
{
	int	i;

	i = 0;
	while (m->input[i])
	{
		if (m->input[i] == '|')
			if (new_tok(m, i))
				return (1);
		i++;
	}
	return (0);
}
