/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tok.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:04:45 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/28 16:42:38 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_TOK_H
# define ENV_TOK_H
# include "env.h"

int		count(t_token *tok, bool is_div);
void	get_idx(t_token *tok, t_env *env);
#endif