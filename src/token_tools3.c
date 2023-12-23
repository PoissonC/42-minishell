/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 09:45:23 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/23 16:49:00 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static bool	new_tok(t_minishell *m, int pos)
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
	new_tok->end_pos = -1;
	new_tok->pos = pos;
	new_tok->is_div = 0;
	return (0);
}

static bool	right_shift(t_minishell *m, int *i)
{
	if (m->input[*i + 1] == '>')
	{
		if (new_tok(m, *i))
			return (1);
		m->t_tail->type = TYPE_REDIR_AP;
		(*i)++;
	}
	else
	{
		if (new_tok(m, *i))
			return (1);
		m->t_tail->type = TYPE_REDIR_OUT;
	}
	return (0);
}

static bool	left_shift(t_minishell *m, int *i)
{
	if (m->input[*i + 1] == '<')
	{
		if (new_tok(m, *i))
			return (1);
		m->t_tail->type = TYPE_HEREDOC;
		(*i)++;
	}
	else
	{
		if (new_tok(m, *i))
			return (1);
		m->t_tail->type = TYPE_REDIR_IN;
	}
	return (0);
}

bool	redir(t_minishell *m)
{
	int	i;

	i = 0;
	while (m->input[i])
	{
		if (m->input[i] == '>')
		{
			if (right_shift(m, &i))
				return (1);
		}
		else if (m->input[i] == '<')
			if (left_shift(m, &i))
				return (1);
		i++;
	}
	return (0);
}
