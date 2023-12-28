/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:04:45 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/28 18:09:37 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "minishell.h"

typedef struct s_env
{
	char	*cont;
	int		*idx;
	int		num;
}				t_env;

char	*get_name(t_minishell *m, t_env *env, char *str, int idx);
bool	copy_env(t_minishell *m, t_env *env, char *env_cont);
char	*get_cont(t_minishell *m, char *name);
#endif