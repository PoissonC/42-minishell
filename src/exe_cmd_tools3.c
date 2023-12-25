/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_tools3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:03:52 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/25 21:27:47 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

bool	env_size_inc(t_minishell *m, char *new_str)
{
	char	**new_env;
	char	*tmp;
	int		size;
	int		i;

	size = 2;
	while (environ[size - 2])
		size++;
	new_env = ft_malloc(sizeof(char *) * size, m->mem_env);
	if (!new_env)
		return (1);
	i = 0;
	while (environ[i])
	{
		new_env[i] = environ[i];
		i++;
	}
	tmp = ft_strdup(new_str);
	ft_lstlast(m->mem_env)->next = ft_lstnew(tmp);
	new_env[i] = tmp;
	new_env[i + 1] = NULL;
	ft_free(environ, m->mem_env);
	environ = new_env;
	return (0);
}

bool	is_exist_export(t_minishell *m, char *target)
{
	int		i;
	int		equal_mark;
	char	*tmp;

	equal_mark = 1;
	while (target[equal_mark])
		if (target[equal_mark++] == '=')
			break ;
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], target, equal_mark) == 0)
		{
			ft_free(environ[i], m->mem_env);
			tmp = ft_strdup(target);
			ft_lstlast(m->mem_env)->next = ft_lstnew(tmp);
			environ[i] = tmp;
			return (1);
		}
		i++;
	}
	return (0);
}

void	m_export(t_minishell *m, char *new_env, char *caller)
{
	if (!is_exist_export(m, new_env))
	{
		if (env_size_inc(m, new_env))
		{
			ft_putstr_fd("minishell: ", 2);
			perror(caller);
			if (m->exe_size != 1)
				exit(errno);
		}
	}
}

void	b_unset(t_minishell *m, int idx)
{
	int	i;

	i = 1;
	while (m->exe[idx].args[i])
	{
		if (getenv(m->exe[idx].args[i]))
			m_unset(m, m->exe[idx].args[i]);
		else
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(m->exe[idx].args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		i++;
	}
	if (m->exe_size != 1)
		exit(0);
}
