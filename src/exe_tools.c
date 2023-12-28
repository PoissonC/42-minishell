/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:46:32 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/28 18:35:31 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

bool	is_parent(t_minishell *m)
{
	if (!m->exe[0].args)
		return (0);
	if (!ft_strncmp(m->exe[0].args[0], "cd", 3))
		return (1);
	if (!ft_strncmp(m->exe[0].args[0], "export", 7))
		return (1);
	if (!ft_strncmp(m->exe[0].args[0], "unset", 6))
		return (1);
	if (!ft_strncmp(m->exe[0].args[0], "exit", 5))
		return (1);
	return (0);
}

static bool	open_rdr(t_rdr *rdr)
{
	if (rdr->type == TYPE_REDIR_OUT)
	{
		rdr->o_fd = open(rdr->fn, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (rdr->o_fd == -1)
			return (1);
	}
	else if (rdr->type == TYPE_REDIR_AP)
	{
		rdr->o_fd = open(rdr->fn, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (rdr->o_fd == -1)
			return (1);
	}
	else if (rdr->type == TYPE_REDIR_IN)
	{
		rdr->o_fd = open(rdr->fn, O_RDONLY);
		if (rdr->o_fd == -1)
			return (1);
	}
	return (0);
}

void	exe_rdr(t_minishell *m)
{
	int	i;
	int	j;

	i = -1;
	while (++i < m->exe_size)
	{
		j = -1;
		while (++j < m->exe[i].rdr_size)
		{
			if (m->exe[i].rdr[j].type >= 1 && m->exe[i].rdr[j].type <= 3)
			{
				if (open_rdr(&(m->exe[i].rdr[j])))
				{
					ft_putstr_fd("minishell: ", 2);
					perror(m->exe[i].rdr[j].fn);
					m->end_stat = errno;
					m->exe[i].rdr[j].if_rdr = 0;
					break ;
				}
				else
					m->exe[i].rdr[j].if_rdr = 1;
			}
		}
	}
}

bool	exe_pipe(t_minishell *m, int idx)
{
	if (idx != m->exe_size - 1)
	{
		if (pipe(m->exe[idx].pipe) == -1)
		{
			perror("minishell");
			return (1);
		}
		if (!m->exe[idx + 1].args)
			close(m->exe[idx].pipe[0]);
	}
	return (0);
}
