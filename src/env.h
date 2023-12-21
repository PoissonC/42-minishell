/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnualman <tnualman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:04:45 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/20 18:12:59 by tnualman         ###   ########.fr       */
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

int		count(t_token *tok, bool is_div);
void	get_idx(t_token *tok, t_env *env);
char	*get_name(t_minishell *m, t_env *env, char *str, int idx);
#endif