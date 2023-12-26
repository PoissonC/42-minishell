/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:51:39 by ychen2            #+#    #+#             */
/*   Updated: 2023/12/26 17:08:57 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# define PROMPT "minishell$ "

extern char					**environ;
extern int					g_sig;
typedef struct s_token		t_token;
typedef struct s_exe		t_exe;
typedef struct s_rdr		t_rdr;
typedef struct s_hdc		t_hdc;

typedef enum e_type
{
	TYPE_PIPE,
	TYPE_REDIR_IN,
	TYPE_REDIR_OUT,
	TYPE_REDIR_AP,
	TYPE_HEREDOC,
	TYPE_COMMAND,
	TYPE_ARG,
	TYPE_FD,
	TYPE_DELIMETER,
	TYPE_FILENAME
}	t_type;

struct s_token
{
	char	*cont;
	t_token	*next;
	int		pos;
	int		end_pos;
	t_type	type;
	bool	is_div;
};

struct s_rdr
{
	int		fd;
	int		o_fd;
	char	*fn;
	t_type	type;
};

struct s_hdc
{
	int		fd;
	char	*eof;
	int		pipe[2];
};

struct s_exe
{
	char	**args;
	t_rdr	*rdr;
	t_hdc	*hdc;
	int		rdr_size;
	int		hdc_size;
	pid_t	pid;
	int		pipe[2];
};

typedef struct s_minishell
{
	struct termios	term_orig;
	char			*path;
	int				a_size;
	int				b_size;
	t_token			*t_head;
	t_token			*t_tail;
	char			*input;
	long long		end_stat;
	t_exe			*exe;
	int				exe_size;
	int				exe_idx;
	int				env_size;
	t_list			*mem;
	t_list			*mem_env;
	bool			is_print_sig;
}				t_minishell;

//loop
void	main_loop(t_minishell *m);

//signal
void	sig_init(void);
void	end_shell(t_minishell *m, int end_code);
void	do_nothing(int signum);
void	read_again(int signum);
void	sig_int(int signum);
void	sig_quit(int signum);
void	sig_block(void);
void	sig_default(t_minishell *m);
void	get_rid_of_sig(t_minishell *m);
void	sig_int_hdc(int signum);

//init
bool	shell_init(t_minishell *m);
bool	env_init(t_minishell *m);

//token
bool	tokenize(t_minishell *m);

//env
bool	get_env(t_minishell *m, t_token *tok, bool is_div);

//parse
bool	parse(t_minishell *m);

//execute
bool	exe(t_minishell *m);
void	b_pwd(t_minishell *m, bool is_print);
bool	is_parent(t_minishell *m);

//for env
void	m_export(t_minishell *m, char *new_env, char *caller);
void	m_unset(t_minishell *m, char *target);
bool	env_size_inc(t_minishell *m, char *new_str);
bool	env_size_dec(t_minishell *m, char *target, int tar_len);
bool	is_exist_export(t_minishell *m, char *target);

#endif