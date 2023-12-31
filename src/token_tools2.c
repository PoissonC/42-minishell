/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 09:45:23 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/31 14:02:59 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static bool	new_tok(t_minishell *m, int size, int pos)
{
	t_token	*new_tok;
	int		i;

	new_tok = ft_malloc(sizeof(t_token), m->mem);
	if (!new_tok)
		return (1);
	ft_memset(new_tok, 0, sizeof(t_token));
	m->t_tail->next = new_tok;
	m->t_tail = new_tok;
	m->a_size++;
	new_tok->cont = ft_malloc(size, m->mem);
	if (!new_tok->cont)
		return (1);
	ft_strlcpy(new_tok->cont, m->input + pos + 1, size);
	new_tok->end_pos = pos + size;
	new_tok->pos = pos;
	new_tok->type = TYPE_ARG;
	i = 0;
	while (i <= size)
	{
		m->input[pos + i] = '\'';
		i++;
	}
	new_tok->is_div = 0;
	return (0);
}

static bool	single(t_minishell *m, int *pos)
{
	int	size;
	int	flag;

	size = 1;
	flag = 1;
	while (m->input[*pos + size])
	{
		if (m->input[*pos + size] == '\'')
		{
			if (new_tok(m, size, *pos))
				return (1);
			*pos += size;
			flag = 0;
			break ;
		}
		size++;
	}
	if (flag)
		return (1);
	return (0);
}

static bool	db(t_minishell *m, int *pos)
{
	int	size;
	int	flag;

	size = 1;
	flag = 1;
	while (m->input[*pos + size])
	{
		if (m->input[*pos + size] == '\"')
		{
			new_tok(m, size, *pos);
			*pos += size;
			flag = 0;
			break ;
		}
		size++;
	}
	if (flag)
		return (1);
	get_env(m, m->t_tail, 0);
	return (0);
}

bool	quote(t_minishell *m)
{
	int	i;

	i = 0;
	while (m->input[i])
	{
		if (m->input[i] == '\'')
		{
			if (single(m, &i))
				return (1);
		}
		else if (m->input[i] == '\"')
			if (db(m, &i))
				return (1);
		i++;
	}
	return (0);
}
