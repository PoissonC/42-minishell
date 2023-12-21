/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:04:45 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/17 15:00:29 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

bool	parse_redir(t_minishell *m);
bool	parse_fd(t_minishell *m);
bool	parse_cmd(t_minishell *m);
t_token	*next_pipe(t_token *now);
bool	rdr_malloc(t_minishell *m, int idx);
void	fill_rdr_nfd(t_exe *exe, int idx, t_token *type, t_token *fn);
void	fill_rdr_fd(t_exe *exe, int idx, t_token *fd, t_token *fn);
#endif