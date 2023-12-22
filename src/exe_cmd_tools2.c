/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:46:32 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/22 17:51:53 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mod_env_cd(t_minishell *m, char *old_pwd)
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
	b_pwd(m, 0);
	ft_lstlast(m->mem)->next = ft_lstnew(tmp);
	tmp = ft_strjoin("PWD=", m->path);
	if (!tmp)
	{
		perror("minishell: cd");
		if (m->exe_size != 1)
			exit(errno);
	}
	m_export(m, tmp, "cd");
	ft_lstlast(m->mem)->next = ft_lstnew(tmp);
}

void	cd_error(t_minishell *m)
{
	perror("minishell: cd");
	if (m->exe_size != 1)
		exit(errno);
}

void	b_cd(t_minishell *m, int idx)
{
	if (ft_strncmp(m->exe[idx].args[1], "~", 2) == 0 || !m->exe[idx].args[1]
		|| ft_strncmp(m->exe[idx].args[1], "~/", 3) == 0)
	{
		if (chdir(getenv("HOME")) != 0)
			cd_error(m);
		mod_env_cd(m, getenv("PWD"));
	}
	else if (ft_strncmp(m->exe[idx].args[1], "-", 2) == 0
		|| ft_strncmp(m->exe[idx].args[1], "-/", 3) == 0)
	{
		if (chdir(getenv("OLDPWD")) != 0)
			cd_error(m);
		printf("%s\n", getenv("OLDPWD"));
		mod_env_cd(m, getenv("PWD"));
	}
	else
	{
		if (chdir(m->exe[idx].args[1]) != 0
			&& ft_strncmp(m->exe[idx].args[1], ".", 2))
			cd_error(m);
		else if (!ft_strncmp(m->exe[idx].args[1], ".", 2))
			cd_error_special(m);
		mod_env_cd(m, getenv("PWD"));
	}
	if (m->exe_size != 1)
		exit(0);
}

static void	b_export_error(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	b_export(t_minishell *m, int idx)
{
	int	i;
	int	j;

	i = 0;
	while (m->exe[idx].args[++i])
	{
		j = 0;
		while (m->exe[idx].args[i][j])
		{
			if (m->exe[idx].args[i][j] == '=' && j != 0)
			{
				m_export(m, m->exe[idx].args[i], "export");
				break ;
			}
			if (!ft_isalnum(m->exe[idx].args[i][j]))
			{
				b_export_error(m->exe[idx].args[i]);
				break ;
			}
			j++;
		}
	}
	if (m->exe_size != 1)
		exit(0);
}
