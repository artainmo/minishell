/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 21:38:20 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/01 06:26:46 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_dollar_quest;
char	*g_prompt;
int		g_exec_status;
int		g_ctrl_d;
int		g_error_minishell;
char	*g_pipe_buffer;

static	char	*ft_isolate_end_path(void)
{
	int		i;
	char	*path_name;
	char	*isol_path;

	if (!(path_name = malloc(100)))
		ft_errnoq();
	if (!(getcwd(path_name, 100)))
		ft_errno();
	i = ft_strlen(path_name);
	while (path_name[i - 1] != '/')
		i--;
	if (!(isol_path = ft_strdup(&path_name[i])))
		ft_errno();
	free(path_name);
	return (isol_path);
}

static	char	*get_prompt(t_shell shell)
{
	char	*username;
	char	*end_path;

	username = env_get_value("USER", shell.shenvp);
	if (!(username = ft_strjoin(username, "\033[1;34m@\033[0;32m")))
		ft_errnoq();
	end_path = ft_isolate_end_path();
	if (!(g_prompt = ft_strjoin(username, end_path)))
		ft_errnoq();
	free(username);
	free(end_path);
	return (g_prompt);
}

static	void	ft_minishell(t_shell *shell, char *line, int ret)
{
	ft_ctrl_signals();
	while (19)
	{
		g_exec_status = 0;
		g_error_minishell = 0;
		g_prompt = get_prompt(*shell);
		if ((ft_printf("\033[0;31m%s\033[0m$ ", g_prompt)) == -1)
			ft_errnoq();
		if ((ret = get_next_line(0, &line)) == -1)
			ft_errno();
		if (line[0] != '\0')
		{
			ft_shellparsing(line, shell);
			if (g_pipe_buffer)
				exec_not_last_pipes(g_pipe_buffer, shell);
			free(g_pipe_buffer);
			g_pipe_buffer = 0;
		}
		else if (g_ctrl_d == 1)
			ft_ctrl_d();
		free(line);
		free(g_prompt);
	}
}

int				main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	shell;
	int		ret;

	(void)argc;
	(void)argv;
	ret = 0;
	line = NULL;
	shell.shenvp = initialize_shenv(envp);
	shell.bsq = 0;
	shell.bdq = 0;
	shell.benc = 0;
	g_dollar_quest = 0;
	ft_minishell(&shell, line, ret);
	exit(0);
}
