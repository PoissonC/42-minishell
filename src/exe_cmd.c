/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:46:32 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/25 21:58:28 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

char	**get_path(t_minishell *m, char *cmd)
{
	char	*tmp;
	char	**ans;
	int		i;

	ans = ft_split(getenv("PATH"), ':');
	if (!ans)
		return (NULL);
	ft_lstlast(m->mem)->next = ft_lstnew(ans);
	i = 0;
	while (ans[i])
	{
		tmp = ans[i];
		ans[i] = ft_strjoin(tmp, "/");
		if (!ans)
			return (NULL);
		free(tmp);
		tmp = ans[i];
		ans[i] = ft_strjoin(tmp, cmd);
		if (!ans)
			return (NULL);
		ft_lstlast(m->mem)->next = ft_lstnew(ans[i]);
		free(tmp);
		i++;
	}
	return (ans);
}

static void	start_exe_rdr(t_minishell *m, int idx)
{
	int		i;

	i = 0;
	while (i < m->exe[idx].rdr_size)
	{
		if (dup2(m->exe[idx].rdr[i].o_fd, m->exe[idx].rdr[i].fd) == -1)
		{
			perror("minishell");
			exit(errno);
		}
		i++;
	}
	m->end_stat = 0;
}

void	child_process(t_minishell *m, int idx)
{
	sig_default(m);
	if (idx > 0)
		close(m->exe[idx - 1].pipe[1]);
	if (idx != m->exe_size - 1)
		close(m->exe[idx].pipe[0]);
	if (idx != m->exe_size - 1)
	{
		dup2(m->exe[idx].pipe[1], STDOUT_FILENO);
		close(m->exe[idx].pipe[1]);
	}
	if (idx != 0)
	{
		dup2(m->exe[idx - 1].pipe[0], STDIN_FILENO);
		close(m->exe[idx - 1].pipe[0]);
	}
	start_exe_rdr(m, idx);
	if (m->exe[idx].hdc_size)
	{
		dup2(m->exe[idx].hdc[m->exe[idx].hdc_size - 1].pipe[0], STDIN_FILENO);
		close(m->exe[idx].hdc[m->exe[idx].hdc_size - 1].pipe[0]);
		close(m->exe[idx].hdc[m->exe[idx].hdc_size - 1].pipe[1]);
	}
	start_exe_cmd(m, idx);
}

void	exe_parent(t_minishell *m)
{
	start_exe_rdr(m, 0);
	if (m->exe[0].hdc_size)
		dup2(m->exe[0].hdc[m->exe[0].hdc_size - 1].pipe[0], STDIN_FILENO);
	exe_builtin(m, 0, 1);
}

bool	exe_cmd(t_minishell *m)
{
	int		i;

	i = -1;
	while (++i < m->exe_size)
	{
		if (exe_pipe(m, i))
			return (1);
		if (m->exe_size > 1 || !is_parent(m))
		{
			if (!m->exe[i++].args)
				continue ;
			m->exe[--i].pid = fork();
			if (m->exe[i].pid == -1)
				return (1);
			if (m->exe[i].pid == 0)
				child_process(m, i);
			if (i != m->exe_size - 1)
				close(m->exe[i].pipe[1]);
		}
		else
			exe_parent(m);
	}
	return (0);
}
