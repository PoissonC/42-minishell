/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:12:46 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/21 20:22:16 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_nothing(int signum)
{
	g_sig = signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	read_again(int signum)
{
	g_sig = signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	printf("\n");
	rl_redisplay();
}

void	sig_int(int signum)
{
	g_sig = signum;
	printf("^C\n");
	exit(130);
}

void	sig_quit(int signum)
{
	g_sig = signum;
	write(1, "^\\Quit: 3\n", 10);
	exit(131);
}

void	sig_int_hdc(int signum)
{
	g_sig = signum;
	printf("\n");
	exit(130);
}
