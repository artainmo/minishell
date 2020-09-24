/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 06:09:21 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/01 06:10:09 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_last_path(char *last_path, t_shell *shell)
{
	char *change_env_value;

	if (!(change_env_value = ft_strjoin("OLDPWD=", last_path)))
	{
		write(1, "D", 1);
		ft_errnoq();
	}
	env_change_value(change_env_value, &shell->shenvp);
	free(change_env_value);
	free(last_path);
}

char	*current_pwd(void)
{
	char *path_name;

	if (!(path_name = malloc(100)))
	{
		write(1, "D", 1);
		ft_errnoq();
	}
	if (!(getcwd(path_name, 100)))
		ft_errno();
	return (path_name);
}
