/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:33:12 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/25 22:02:15 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_shell_lv(t_minishell *m)
{
	char	*tmp;
	int		lv;
	char	*lv_tmp;

	lv = ft_atoi(getenv("SHLVL")) + 1;
	lv_tmp = ft_itoa(lv);
	tmp = ft_strjoin("SHLVL=", lv_tmp);
	if (!tmp)
	{
		perror("minishell: cd");
		exit(1);
	}
	free(lv_tmp);
	m_export(m, tmp, NULL);
	ft_lstlast(m->mem_env)->next = ft_lstnew(tmp);
}

static void	start_env(t_minishell *m)
{
	char	*tmp;

	m_unset(m, "OLDPWD");
	b_pwd(m, 0);
	tmp = ft_strjoin("PWD=", m->path);
	if (!tmp)
	{
		perror("minishell: cd");
		exit(1);
	}
	m_export(m, tmp, NULL);
	ft_lstlast(m->mem_env)->next = ft_lstnew(tmp);
	handle_shell_lv(m);
}

void	get_rid_of_sig(t_minishell *m)
{
	struct termios	termios;

	ft_memset(&m->term_orig, 0, sizeof(m->term_orig));
	tcgetattr(STDIN_FILENO, &m->term_orig);
	termios = m->term_orig;
	termios.c_lflag &= ~ECHOCTL;
	termios.c_lflag |= (ECHO | ICANON | ISIG);
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
}

int	main(void)
{
	t_minishell	m;

	sig_init();
	get_rid_of_sig(&m);
	m.end_stat = 0;
	m.mem_env = ft_lstnew(NULL);
	if (!m.mem_env)
	{
		perror("minishell");
		exit(1);
	}
	shell_init(&m);
	if (env_init(&m))
	{
		perror("minishell");
		exit(1);
	}
	start_env(&m);
	main_loop(&m);
	ft_free_all(m.mem_env);
	exit(0);
}
