/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:31:45 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/21 18:06:43 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	get_arg_size(t_token *now)
{
	int	ct;

	ct = 1;
	while (now)
	{
		if (now->type == TYPE_PIPE)
			break ;
		if (now->type == TYPE_COMMAND || now->type == TYPE_ARG)
			ct++;
		now = now->next;
	}
	return (ct);
}

static void	fill_args(t_minishell *m, int idx, int arg_size, t_token *now)
{
	int		i;

	i = 0;
	while (i < arg_size - 1)
	{
		if (now->type == TYPE_COMMAND || now->type == TYPE_ARG)
			m->exe[idx].args[i++] = now->cont;
		now = now->next;
	}
	m->exe[idx].args[i] = NULL;
}

bool	parse_cmd(t_minishell *m)
{
	int		i;
	int		arg_size;
	t_token	*now;

	now = m->t_head->next;
	i = 0;
	while (i < m->exe_size && now)
	{
		arg_size = get_arg_size(now);
		if (arg_size != 1)
		{
			m->exe[i].args = ft_malloc(arg_size * sizeof(char *), m->mem);
			if (!m->exe[i].args)
				return (1);
			fill_args(m, i, arg_size, now);
		}
		now = next_pipe(now);
		i++;
	}
	return (0);
}
