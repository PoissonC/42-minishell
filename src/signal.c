/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:53:20 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/21 20:58:50 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_default(t_minishell *m)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);(void)m;
	// tcsetattr(STDIN_FILENO, TCSANOW, &m->term_orig_in);
	// tcsetattr(STDOUT_FILENO, TCSANOW, &m->term_orig_);
}

void	sig_block(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_init(void)
{
	signal(SIGINT, read_again);
	signal(SIGQUIT, do_nothing);
}
