/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:33:12 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/21 19:47:46 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restart_lp(t_minishell *m)
{
	ft_free_all(m->mem);
	free(m->mem);
	free(m->input);
	shell_init(m);
	sig_init();
}

static void	main_loop_process(t_minishell *m)
{
	if (tokenize(m))
	{
		ft_putstr_fd(
			"minishell: syntax error near unexpected token `newline'\n", 2);
		restart_lp(m);
		return ;
	}
	if (parse(m))
	{
		ft_putstr_fd(
			"minishell: parsing error\n", 2);
		restart_lp(m);
		return ;
	}
	if (exe(m))
		m->end_stat = 1;
	restart_lp(m);
}

void	main_loop(t_minishell *m)
{
	while (1)
	{
		get_rid_of_sig(m);
		m->input = readline(PROMPT);
		if (!m->input)
			break ;
		if (m->input[0] == '\0')
		{
			restart_lp(m);
			continue ;
		}
		add_history(m->input);
		if (g_sig == SIGINT)
		{
			m->end_stat = 1;
			g_sig = 0;
		}
		main_loop_process(m);
	}
}
