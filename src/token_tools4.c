/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 09:42:14 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/23 16:48:58 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static void	type_cmd_dlt_fn(t_token *now, t_token *prev)
{
	if (prev->type == TYPE_PIPE || prev->type == TYPE_FILENAME)
		now->type = TYPE_COMMAND;
	else if (prev->type == TYPE_DELIMETER)
		now->type = TYPE_COMMAND;
	else if (prev->type == TYPE_HEREDOC)
		now->type = TYPE_DELIMETER;
	else if (prev->type == TYPE_REDIR_AP
		|| prev->type == TYPE_REDIR_IN || prev->type == TYPE_REDIR_OUT)
		now->type = TYPE_FILENAME;
	else
		now->type = TYPE_ARG;
}

//change prev type
static bool	type_fd(t_token *prev, int pos)
{
	if (ft_strlen(prev->cont) != 1)
		return (0);
	if (!ft_isdigit(prev->cont[0]))
		return (0);
	if (prev->end_pos + 1 != pos)
		return (0);
	prev->type = TYPE_FD;
	return (1);
}

static void	type_init(t_minishell *m, t_token **now, t_token **prev)
{
	(*now) = m->t_head->next;
	if ((*now)->next)
	{
		if ((*now)->next->type == TYPE_REDIR_OUT
			|| (*now)->next->type == TYPE_REDIR_AP)
		{
			if (!type_fd((*now), (*now)->next->pos))
				(*now)->type = TYPE_COMMAND;
		}
		else if ((*now)->end_pos != -1)
			(*now)->type = TYPE_COMMAND;
	}
	else if ((*now)->end_pos != -1)
		(*now)->type = TYPE_COMMAND;
	*prev = *now;
	(*now) = (*now)->next;
}

void	type(t_minishell *m)
{
	t_token	*now;
	t_token	*prev;

	type_init(m, &now, &prev);
	while (now)
	{
		if (prev->type != TYPE_COMMAND && now->end_pos != -1)
			type_cmd_dlt_fn(now, prev);
		else if ((prev->type == TYPE_ARG || prev->type == TYPE_COMMAND)
			&& (now->type >= 1 && now->type <= 4))
			type_fd(prev, now->pos);
		else if (now->end_pos != -1)
			now->type = TYPE_ARG;
		prev = now;
		now = now->next;
	}
}
