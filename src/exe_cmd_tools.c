/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:46:32 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/23 16:50:36 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

static void	b_echo_n(t_exe exe, int i)
{
	while (exe.args[i])
	{
		printf("%s", exe.args[i++]);
		if (exe.args[i])
			printf(" ");
	}
	exit(0);
}

bool	skip_option(t_exe exe, int *idx)
{
	size_t	i;
	bool	flag;

	flag = false;
	while (exe.args[*idx])
	{
		if (exe.args[*idx][0] == '-' && exe.args[*idx][1])
		{
			i = 0;
			while (exe.args[*idx][++i])
			{
				if (exe.args[*idx][i] == 'n')
					flag = true;
				else
					break ;
			}
			if (i == ft_strlen(exe.args[*idx]) && exe.args[*idx][i] != '-')
				(*idx)++;
			else
				break ;
		}
		else
			break ;
	}
	return (flag);
}

void	b_echo(t_minishell *m, int idx)
{
	int		i;
	bool	flag;

	i = 1;
	flag = skip_option(m->exe[idx], &i);
	if (flag)
		b_echo_n(m->exe[idx], i);
	else
	{
		while (m->exe[idx].args[i])
		{
			printf("%s", m->exe[idx].args[i++]);
			if (m->exe[idx].args[i])
				printf(" ");
		}
		printf("\n");
	}
	exit(0);
}

void	b_pwd(t_minishell *m, bool is_print)
{
	if (getcwd(m->path, PATH_MAX) != NULL)
	{
		if (is_print)
		{
			printf("%s\n", m->path);
			exit(0);
		}
	}
	else if (is_print == 1)
	{
		m->path = getenv("PWD");
		printf("%s\n", m->path);
		m->end_stat = 1;
		if (!is_parent(m))
			exit(1);
	}
	else
		m->path = getenv("PWD");
}

void	b_env(t_minishell *m, int idx)
{
	int	i;

	if (m->exe[idx].args[1])
	{
		ft_putstr_fd("minishell: we don't handle options or arguments.\n", 2);
		exit(1);
	}
	i = 0;
	while (environ[i])
		printf("%s\n", environ[i++]);
	exit(0);
}
