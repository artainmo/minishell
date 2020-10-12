/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 07:30:55 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/01 07:31:37 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	void	env_error_argument(char **commands, int *i)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(commands[*i + 1], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	while (commands[*i + 1])
		(*i)++;
}

void			ft_env(char **commands, int *i, t_shell *shell)
{
	if (commands[*i + 1])
		env_error_argument(commands, i);
	else
		env_display(shell->shenvp, 0);
	g_dollar_quest = 0;
}
