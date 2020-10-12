/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:29:25 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/02 09:57:34 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "utils/libft/libft.h"
# include "utils/get_next_line/get_next_line.h"
# include "utils/ft_printf/printf.h"

typedef struct	s_shell
{
	char		bsq;
	char		bdq;
	char		benc;
	char		**shenvp;
	int			double_rflag;
	int			right_left;
	char		*norm_right_redirec_loop;

}				t_shell;

void			ft_shellparsing(char *line, t_shell *shell);
char			next_redirection(char *command,
				char **next_command, t_shell *shell);
char			*too_much_left(char *command);
void			too_much_right(char *command,
				char *next_command, t_shell *shell);
void			ft_errno(void);
void			ft_errnom(char *message);
void			ft_errnoq(void);
void			ft_malloc_error(void);
void			ft_echo(char **commands, int *i);
void			ft_cd(char **commands, int *i, t_shell *shell);
void			init_last_path(char *last_path, t_shell *shell);
char			*current_pwd();
void			ft_exit(char **argv, int *i);
void			ft_pwd(char **commands, int *i);
void			ft_exec_cat(char **commands, int *i);
void			ft_execute_program(char **commands, int *i, t_shell *shell);
void			cat_file(char *executable);
void			ft_env(char **commands, int *i, t_shell *shell);
void			ft_export(char **commands, int *i, t_shell *shell);
void			ft_unset(char **commands, int *i, t_shell *shell);
void			ft_pipe(char *commands, char *next_command, t_shell *shell);
void			exec_not_last_pipes(char *command, t_shell *shell);
int				pipe_is_last_command_test(char *command);
void			ft_right_redirection(char *command,
				char *next_command, t_shell *shell);
char			*ft_set_right_redir_pipe(char *next_cmd);
void			ft_left_redirection(char *command,
				char *next_command, t_shell *shell);
void			double_left_redirection(char *command, char *next_cmd,
				t_shell *shell, char **normlmfao);
char			*dup_next_redirection(char *command, int *double_flag);
char			*goto_next_redirection(char *command);
char			get_next_redirection_type(char *command);
int				quotes_token_test(char *command, int i);
int				comm_red_lenght(char *command, char token);
void			close_fds_delete_files(int fd, int fd2, int fd3, int fd4);
char			*parse_rightredirection_type(char *command);
char			*parse_leftredirection_type(char *command);
int				get_command_status(char *command);
char			*get_begin_comm(char *command);
int				right_open_fd(char *command, t_shell *shell, int error);
int				left_open_fd(char *command, int error);
char			*get_filename_no_spaces(char *filename);
char			**split_redirection_commands(char *command);
char			*env_get_value(char *env_name, char **envp);
int				env_change_value(char *env_var, char ***shenvp);
char			**get_env(char *env_name, char **envp);
void			env_display(char **shenvp, char mod);
int				unset(char *env_name, char ***shenvp);
char			*env_extract_value(char *env);
int				strcmptc(const char *s1, const char *s2, char limit);
int				ft_strlentoc(char *s, char stop);
char			**ft_realloc_dptr(char **ptr, int size);
char			**initialize_shenv(char **envp);
int				n_env(char **envp);
char			**free_prev_str(char **strs, int i);
int				add_new_env(char ***shenvp, char *env_name, char *new_value);
char			**ft_sralloc_dptr(char **ptr, int size);
char			*env_substitution(char *line, t_shell shell);
int				toggle_bool(t_shell *shell, char *env_split, int j);
char			*parse_quotes(char *line, t_shell *shell, char eol);
void			quotes_parse_arg(char **words, int i, t_shell *shell);
void			tabtobell(char **line);
int				splitlen(char **split);
int				wexitstatus(int status);
void			ft_ctrl_signals();
void			ft_ctrl_d();
int				toggle_bool(t_shell *shell, char *env_split, int j);
void			dollar_quest(char **words);
int				l_has_empty_cmd(char *line, t_shell shell);
int				toggle_quotesb(char c, t_shell *shell);
char			*ft_strchr_wquotes(char *s, char *ch, t_shell shell);
int				parse_err(char *line, t_shell shell);
void			display_err(int ret, int *i);
void			zero_that(char *bsq, char *bdq, char *benc);
char			*addonec(char *s1, char c);
char			*mright_redir_parse(char **cmds);
int				double_lredirect_only(char *cmd);
void			lredirect_args(char **arg, char *cmd, t_shell *shell);
char			*ft_left_right_redirection_parse(char *command,
				char **next_command);
void			mix_right_left_redirec(char *command, t_shell *shell);
void			free_dlr(char *s, char **ds, char **ds2);
int				norm_free(char **s);
char			**ft_split_cmd(char const *s, char c);
int				empty_dlredir(char *line, t_shell shell);
char			**free_ssplit(char **s, int i, int *cc);
int				free_split(char **split, char *str);
int				redinq(char *command);
char			*parse_quotes_nof(char *line, t_shell *shell, char eol);
int				is_token_edq(char c);

extern int		g_dollar_quest;
extern char		*g_prompt;
extern int		g_exec_status;
extern int		g_ctrl_d;
extern int		g_error_minishell;
extern char		*g_pipe_buffer;

#endif
