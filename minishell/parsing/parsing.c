/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 07:13:06 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/04 20:56:32 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	ft_check_word(char **words, int *i, t_shell *shell)
{
	if ((ft_strcmp(words[*i], "echo")))
		ft_echo(words, i);
	else if ((ft_strcmp(words[*i], "cd")))
		ft_cd(words, i, shell);
	else if ((ft_strcmp(words[*i], "pwd")))
		ft_pwd(words, i);
	else if ((ft_strcmp(words[*i], "export")))
		ft_export(words, i, shell);
	else if ((ft_strcmp(words[*i], "unset")))
		ft_unset(words, i, shell);
	else if ((ft_strcmp(words[*i], "env")))
		ft_env(words, i, shell);
	else if ((ft_strcmp(words[*i], "exit")))
		ft_exit(words, i);
	else
		ft_execute_program(words, i, shell);
}

static	void	ft_check_words(char *commands, t_shell *shell)
{
	int		i;
	char	**words;

	i = -1;
	if (!(words = ft_split_cmd(commands, ' ')))
		ft_errnoq();
	dollar_quest(words);
	while (words[++i])
		words[i] = parse_quotes(words[i], shell, (!words[i + 1]) ? 1 : 0);
	i = 0;
	while (words[i])
	{
		ft_check_word(words, &i, shell);
		i++;
	}
	zero_that(&shell->bsq, &shell->bdq, &shell->benc);
	double_str_free(words);
}

static	void	mix_redirec_call(char *l_r_comm, char *next_comm, t_shell *s)
{
	mix_right_left_redirec(l_r_comm, s);
	if (next_comm)
		ft_shellparsing(next_comm, s);
	free(next_comm);
}

static	void	ft_check_inner_commands(char **cmd, t_shell *sh, int rq)
{
	char	*n_cmd;
	char	*l_r_com;
	char	redirec_type;
	char	**dl_redir;

	n_cmd = NULL;
	if (!rq && (l_r_com = ft_left_right_redirection_parse(*cmd, &n_cmd)))
	{
		n_cmd = (n_cmd) ? parse_quotes_nof(n_cmd, sh, 1) : 0;
		mix_redirec_call(l_r_com, n_cmd, sh);
	}
	else if (!rq && (redirec_type = next_redirection(*cmd, &n_cmd, sh)))
	{
		n_cmd = (n_cmd) ? parse_quotes_nof(n_cmd, sh, 1) : 0;
		if (!(dl_redir = NULL) && redirec_type == '|')
			ft_pipe(*cmd, n_cmd, sh);
		else if (redirec_type == '>')
			too_much_right(*cmd, n_cmd, sh);
		else if (redirec_type == '<')
			ft_left_redirection(*cmd, n_cmd, sh);
		else if (redirec_type == 'l' && !too_much_left(*cmd))
			double_left_redirection(*cmd, n_cmd, sh, dl_redir);
	}
	else
		ft_check_words(*cmd, sh);
}

void			ft_shellparsing(char *line, t_shell *shell)
{
	int		ir[3];
	char	**c;
	char	*line_with_env;

	if (line[0] == 0)
		return ;
	if (!(line_with_env = env_substitution(line, *shell)))
		ft_errno();
	ir[1] = parse_err(line_with_env, *shell);
	if ((ir[0] = l_has_empty_cmd(line_with_env, *shell)) == -1)
		ft_putstr_fd("minishell: syntax error near unexpected token `;'\n", 2);
	else if (!double_lredirect_only(line) && (ir[0] = -1))
		ft_putstr_fd("minishell: syntax error extra redir with dl redir.\n", 2);
	else if (empty_dlredir(line_with_env, *shell) && (ir[0] = -1))
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n"
				, 2);
	else
		display_err(ir[1], &(ir[0]));
	if (!(c = ft_split_cmd(line_with_env, ';')))
		ft_errnoq();
	while (ir[0] != -1 && c[ir[0]] && ((ir[1] = redinq(c[ir[0]])) || !ir[1]))
		ft_check_inner_commands(&c[ir[0]++], shell, ir[1]);
	free(line_with_env);
	double_str_free(c);
}
