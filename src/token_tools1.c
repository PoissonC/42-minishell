/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:17:18 by yu                #+#    #+#             */
/*   Updated: 2023/12/25 22:18:07 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static bool	new_tok(t_minishell *m, char *cont, int size, int idx)
{
	t_token	*new_tok;

	new_tok = ft_malloc(sizeof(t_token), m->mem);
	if (!new_tok)
		return (1);
	new_tok->next = NULL;
	new_tok->cont = NULL;
	new_tok->type = TYPE_ARG;
	m->t_tail->next = new_tok;
	m->t_tail = new_tok;
	m->b_size++;
	new_tok->cont = ft_malloc(size + 1, m->mem);
	if (!new_tok->cont)
		return (1);
	ft_strlcpy(new_tok->cont, cont, size + 1);
	new_tok->end_pos = idx + size;
	new_tok->pos = idx + 1;
	new_tok->is_div = 0;
	return (0);
}

static int	fill_mark(int *mark, char *str, char *charset)
{
	int	num;
	int	i;
	int	j;

	if (ft_strlen(str) == 0 || !mark)
		return (-1);
	num = 0;
	i = 0;
	mark[num++] = -1;
	while (str[i])
	{
		j = 0;
		while (charset[j])
		{
			if (charset[j] == str[i])
				mark[num++] = i;
			j++;
		}
		i++;
	}
	mark[num] = ft_strlen(str);
	return (num);
}

bool	minishell_strtok(t_minishell *m, char *str, char *charset)
{
	int		*mk;
	int		num;
	int		i;

	mk = (int *)ft_malloc(sizeof(int) * (ft_strlen(str) + 2), m->mem);
	if (!mk)
		return (1);
	num = fill_mark(mk, str, charset);
	i = 0;
	while (i < num)
	{
		if (mk[i + 1] - mk[i] > 1)
		{
			if (new_tok(m, str + mk[i] + 1, mk[i + 1] - mk[i] - 1, mk[i]))
				return (1);
			get_env(m, m->t_tail, 1);
		}
		i++;
	}
	ft_free(mk, m->mem);
	return (0);
}

bool	normal(t_minishell *m)
{
	if (minishell_strtok(m, m->input, " \t\n\'|<>"))
		return (1);
	return (0);
}
