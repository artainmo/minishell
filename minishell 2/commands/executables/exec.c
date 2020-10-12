/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 07:36:13 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/02 17:59:45 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** MOD 1 silences, errno error messages
*/

static	int	time_to_execve(const char *path, char *const argv[]
		, char **shenvp, char mod)
{
	pid_t	pid;
	int		ret_c;

	g_exec_status = 1;
	if ((pid = fork()) < 0)
	{
		ft_errno();
		exit(0);
	}
	if (!pid)
	{
		if (execve(path, argv, shenvp) < 0)
		{
			if (!mod)
				ft_errnom((char *)path);
			if (errno == 13)
				exit(126);
			if (errno == 2)
				exit(127);
		}
		exit(0);
	}
	waitpid(pid, &ret_c, 0);
	g_dollar_quest = wexitstatus(ret_c);
	return (g_dollar_quest);
}

static	int	exec_from_path_env(const char *path, char *const argv[],
		char **shenvp)
{
	char	*env_and_path;
	char	*tmp;
	char	**paths;
	int		i;
	int		ret;

	i = 0;
	if (!(env_and_path = env_get_value("PATH", shenvp)))
		return (-1);
	if (!(paths = ft_split(env_and_path, ':')))
		return (0);
	while (paths[i])
	{
		if (!(tmp = ft_strjoin(paths[i++], "/")) ||
				!(env_and_path = ft_strjoin(tmp, path)))
			return (0);
		free(tmp);
		if (!(ret = time_to_execve(env_and_path, argv, shenvp, 1)))
			return (free_split(paths, env_and_path));
		free(env_and_path);
		if (ret != 127)
			return (norm_free(paths));
	}
	free_split(paths, 0);
	return (-1);
}

static	int	execute(const char *path, char *const argv[], char **shenvp)
{
	int ret;

	if (ft_strchr(path, '/'))
		time_to_execve(path, argv, shenvp, 0);
	else
	{
		if ((ret = exec_from_path_env(path, argv, shenvp)) == -1)
		{
			g_error_minishell = 1;
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd((char *)path, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		else if (!ret)
			ft_errnoq();
	}
	return (1);
}

static	int	set_argvz(char ***argv, char *path)
{
	free(*argv);
	if (!(*argv = malloc(2 * sizeof(char *))))
		ft_errnoq();
	if (!((*argv)[0] = ft_strdup(path)))
		ft_errnoq();
	(*argv)[1] = NULL;
	return (1);
}

void		ft_execute_program(char **cmds, int *i, t_shell *shell)
{
	char	**argv;
	char	*path;
	int		l;

	l = 0;
	path = cmds[*i];
	if (!(argv = malloc(sizeof(char *) * (ft_count_words(cmds) + 1))))
		ft_errnoq();
	if (!cmds[*i + 1])
		set_argvz(&argv, path);
	else
	{
		while (cmds[*i])
		{
			if (!(argv[l++] = ft_strdup(cmds[(*i)++])))
				ft_errnoq();
		}
		argv[l] = 0;
		*i = *i - 1;
	}
	dollar_quest(argv);
	execute(path, argv, shell->shenvp);
	double_str_free(argv);
}
