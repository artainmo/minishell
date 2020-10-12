/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 06:01:17 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/01 06:02:05 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	pwd_exec(void)
{
	char	*path_name;

	if (!(path_name = malloc(100)))
		ft_errnoq();
	if (!(getcwd(path_name, 100)))
		ft_errno();
	if ((ft_printf("%s\n", path_name)) == -1)
		ft_errnoq();
	free(path_name);
}

void			ft_pwd(char **commands, int *i)
{
	pwd_exec();
	while (commands[*i + 1])
		(*i)++;
	g_dollar_quest = 0;
}
