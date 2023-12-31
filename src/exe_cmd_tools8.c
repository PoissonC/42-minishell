/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_tools8.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 21:29:19 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/25 21:30:33 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	b_cd_home(t_minishell *m, int idx)
{
	if (chdir(getenv("HOME")) != 0)
		cd_error(m, idx);
	mod_env_cd(m, getenv("PWD"));
}
