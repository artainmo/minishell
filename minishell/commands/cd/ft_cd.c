/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 06:03:36 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/04 23:26:46 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	void	ft_cd_void(t_shell *shell)
{
	char *home_directory;

	if (!(home_directory = env_get_value("HOME", shell->shenvp)))
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		return ;
	}
	if (chdir(home_directory) == -1)
		ft_errno();
}

static	void	cd_rel_path(char **comm, int *i, char *path_n)
{
	char *new_path_name;

	*i = *i + 1;
	if (!(path_n = ft_strjoin(path_n, "/")))
		ft_errnoq();
	if (!(new_path_name = ft_strjoin(path_n, comm[*i])))
		ft_errnoq();
	free(path_n);
	if (chdir(new_path_name) == -1)
		ft_errnom(comm[*i]);
	free(new_path_name);
}

static	void	ft_cd_absolute_path(char *absolute_path, int *i)
{
	if (chdir(absolute_path) == -1)
		ft_errnom(absolute_path);
	*i = *i + 1;
}

static	void	ft_cd_last_path(char **commands, int *i, t_shell *shell)
{
	char *last_path_name;

	*i = *i + 1;
	if (commands[*i + 1])
	{
		ft_putstr_fd("cd : string not in pwd: -\n", 2);
		while (commands[*i + 1])
			*i = *i + 1;
	}
	else
	{
		if (!(last_path_name = env_get_value("OLDPWD", shell->shenvp)))
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		else
		{
			if (chdir(last_path_name) == -1)
				ft_errno();
			ft_putendl_fd(last_path_name, 1);
		}
	}
}

void			ft_cd(char **commands, int *i, t_shell *shell)
{
	char	*path_name;
	char	*old_pwd;

	old_pwd = current_pwd();
	if (!(path_name = malloc(100)))
		ft_errnoq();
	if (!(getcwd(path_name, 100)))
		ft_errno();
	if (!commands[*i + 1])
		ft_cd_void(shell);
	else if (commands[*i + 1][0] == '/')
		ft_cd_absolute_path(commands[*i + 1], i);
	else if (commands[*i + 1][0] == '-' && !commands[*i + 1][1])
		ft_cd_last_path(commands, i, shell);
	else
		cd_rel_path(commands, i, path_name);
	init_last_path(old_pwd, shell);
	free(path_name);
	g_dollar_quest = 0;
}
