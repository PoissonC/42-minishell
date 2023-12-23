/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:45:35 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/23 17:06:43 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "minishell.h"

typedef struct s_sort
{
	t_token	*a_now;
	t_token	*b_now;
	int		idx_a;
	int		idx_b;
}				t_sort;

bool	quote(t_minishell *m);
bool	normal(t_minishell *m);
bool	redir(t_minishell *m);
void	sort(t_minishell *m);
bool	minishell_strtok(t_minishell *m, char *str, char *charset);
bool	join(t_minishell *m);
bool	pipeline(t_minishell *m);
void	type(t_minishell *m);

#endif