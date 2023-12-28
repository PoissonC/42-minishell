/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 23:18:23 by yu                #+#    #+#             */
/*   Updated: 2023/12/28 18:12:42 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

static void	print_warning(char *eof)
{
	printf("minishell: warning: here-document");
	printf(" delimited by end-of-file (wanted `%s')\n", eof);
}

static void	hdc_write(t_hdc hdc, char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '\0')
		write(hdc.pipe[1], &buf[i++], 1);
	free(buf);
	write(1, "> ", 2);
}

static void	start_exe_hdc(t_minishell *m, t_hdc hdc)
{
	char	*buf;
	int		size;

	signal(SIGINT, sig_int_hdc);
	size = ft_strlen(hdc.eof);
	write(1, "> ", 2);
	buf = get_next_line(0);
	while (buf)
	{
		if (ft_strncmp(buf, hdc.eof, size) == 0)
			if (buf[size] == '\n')
				break ;
		if (get_env_str(m, &buf))
		{
			m->end_stat = 1;
			return ;
		}
		hdc_write(hdc, buf);
		buf = get_next_line(0);
	}
	if (!buf)
		print_warning(hdc.eof);
	exit(0);
}

static bool	parent_process(int *status)
{
	wait(status);
	if (WIFEXITED(*status))
	{
		*status = WEXITSTATUS(*status);
		return (*status);
	}
	else if (WIFSIGNALED(*status))
	{
		*status = WTERMSIG(*status) + 128;
		return (1);
	}
	return (1);
}

bool	exe_hdc(t_minishell *m)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	while (i < m->exe_size)
	{
		j = 0;
		while (j < m->exe[i].hdc_size)
		{
			if (pipe(m->exe[i].hdc[j].pipe) == -1)
				return (1);
			if (fork() == 0)
				start_exe_hdc(m, m->exe[i].hdc[j]);
			close(m->exe[i].hdc[j].pipe[1]);
			if (parent_process(&status))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
