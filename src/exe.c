/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:38:57 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/25 21:24:14 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	end_exe(t_minishell *m, int *status)
{
	int	i;

	i = 0;
	while (i < m->exe_size)
	{
		if (m->exe[i].args)
			wait(status);
		else
		{
			*status = 0;
			break ;
		}
		if (WIFEXITED(*status))
			*status = WEXITSTATUS(*status);
		else if (WIFSIGNALED(*status))
			*status = WTERMSIG(*status) + 128;
		if (*status == 130 && m->is_print_sig)
			printf("^C\n");
		else if (*status == 131 && m->is_print_sig)
			printf("^\\Quit: 3\n");
		if (*status == 130 || *status == 131)
			m->is_print_sig = 0;
		i++;
	}
}

bool	exe(t_minishell *m)
{
	int	status;
	int	i;

	if (exe_hdc(m))
		return (1);
	if (exe_rdr(m))
		return (1);
	if (exe_cmd(m))
		return (1);
	i = 0;
	while (i < m->exe_size)
	{
		close(m->exe[i].pipe[0]);
		close(m->exe[i++].pipe[1]);
	}
	if (!is_parent(m) || m->exe_size != 1)
	{
		end_exe(m, &status);
		m->end_stat = status;
	}
	return (0);
}
