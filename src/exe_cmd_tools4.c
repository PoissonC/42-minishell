/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_tools4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:20:16 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/25 21:04:27 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	reset_env(t_minishell *m, char **new_env, int tar_idx)
{
	int	i;

	i = -1;
	while (++i != tar_idx)
		new_env[i] = environ[i];
	while (environ[i + 1])
	{
		new_env[i] = environ[i + 1];
		i++;
	}
	new_env[i] = NULL;
	ft_free(environ[tar_idx], m->mem_env);
	environ = new_env;
}

bool	env_size_dec(t_minishell *m, char *target, int tar_len)
{
	char	**new_env;
	int		i;
	int		tar_idx;

	tar_idx = -1;
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], target, tar_len) == 0)
			if (environ[i][tar_len] == '=')
				tar_idx = i;
		i++;
	}
	new_env = ft_malloc(sizeof(char *) * i, m->mem_env);
	if (!new_env)
		return (1);
	if (tar_idx != -1)
		reset_env(m, new_env, tar_idx);
	else
		return (1);
	return (0);
}

void	m_unset(t_minishell *m, char *target)
{
	if (env_size_dec(m, target, ft_strlen(target)))
	{
		if (errno == ENOMEM)
		{
			perror("minishell: unset:");
			m->end_stat = errno;
			if (m->exe_size != 1)
				exit(errno);
		}
	}
}

void	exe_builtin(t_minishell *m, int idx, bool is_print)
{
	if (!ft_strncmp(m->exe[idx].args[0], "echo", 5))
		b_echo(m, idx);
	if (!ft_strncmp(m->exe[idx].args[0], "cd", 3))
		b_cd(m, idx);
	if (!ft_strncmp(m->exe[idx].args[0], "pwd", 4))
		b_pwd(m, 1);
	if (!ft_strncmp(m->exe[idx].args[0], "export", 7))
		b_export(m, idx);
	if (!ft_strncmp(m->exe[idx].args[0], "unset", 6))
		b_unset(m, idx);
	if (!ft_strncmp(m->exe[idx].args[0], "env", 4))
		b_env(m, idx);
	if (!ft_strncmp(m->exe[idx].args[0], "exit", 5))
		b_exit(m, idx, is_print);
}

void	b_cd_handle(t_minishell *m, int idx)
{
	int	flag;
	int	cmp;

	flag = chdir(m->exe[idx].args[1]);
	cmp = ft_strncmp(m->exe[idx].args[1], ".", 2);
	if (flag == -1)
		cd_error(m, idx);
	else if (!cmp)
	{
		if (access(getenv("PWD"), F_OK) != 0)
			cd_error_special(m);
		else
			mod_env_cd(m, getenv("PWD"));
	}
	else
		mod_env_cd(m, getenv("PWD"));
}
