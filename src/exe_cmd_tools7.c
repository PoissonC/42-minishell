/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_tools7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:17:31 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/28 18:32:36 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

static void	mod_env_cd_oldpwd(t_minishell *m, char *old_pwd)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", old_pwd);
	if (!tmp)
	{
		perror("minishell: cd");
		if (m->exe_size != 1)
			exit(errno);
	}
	m_export(m, tmp, "cd");
	free(tmp);
}

void	mod_env_cd_special(t_minishell *m, char *old_pwd)
{
	char	*tmp;
	char	*new_pwd;

	mod_env_cd_oldpwd(m, old_pwd);
	b_pwd(m, 0);
	tmp = ft_strjoin("PWD=", m->path);
	if (!tmp)
	{
		perror("minishell: cd");
		if (m->exe_size != 1)
			exit(errno);
	}
	new_pwd = ft_strjoin(tmp, "/.");
	if (!tmp)
	{
		free(tmp);
		perror("minishell: cd");
		if (m->exe_size != 1)
			exit(errno);
	}
	m_export(m, new_pwd, "cd");
	free(new_pwd);
	free(tmp);
}

void	cd_error_special(t_minishell *m)
{
	ft_putstr_fd("cd: error retrieving current directory: getcwd:", 2);
	ft_putstr_fd(" cannot access parent directories:", 2);
	ft_putstr_fd(" No such file or directory\n", 2);
	mod_env_cd_special(m, getenv("PWD"));
	if (m->exe_size != 1)
		exit(1);
	m->end_stat = 1;
}

void	is_a_dir(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": is a directory\n", 2);
	exit(126);
}

void	check_if_dir(char *cmd)
{
	struct stat	statbuf;

	if (stat(cmd, &statbuf) != 0)
		return ;
	if (S_ISDIR(statbuf.st_mode))
		is_a_dir(cmd);
}
