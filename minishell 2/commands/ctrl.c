/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 05:57:21 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/01 05:59:29 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** ctrl-\ corresponds to the signal SIGQUIT
** ctrl-d indicates EOF on input, read returns 0 when end of file, gnl returns
** -2 on end of file
*/

void			ft_ctrl_d(void)
{
	g_ctrl_d = 0;
	ft_exit(0, 0);
}

/*
** ctrl-c corresponds to the signal SIGINT
*/

static	void	ctrl_backslash(int signal)
{
	(void)signal;
	if (!g_exec_status)
		g_exec_status = 0;
	else
	{
		if (!(ft_printf("Quit: 3\n")))
			ft_errnoq();
		g_exec_status = 0;
	}
}

static	void	ctrl_c(int signal)
{
	(void)signal;
	if (g_exec_status)
		write(1, "\n", 1);
	else
	{
		write(1, "\n", 1);
		if ((ft_printf("\033[0;31m%s\033[0m$ ", g_prompt)) == -1)
			ft_errnoq();
	}
	g_dollar_quest = 1;
}

void			ft_ctrl_signals(void)
{
	g_ctrl_d = 0;
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_backslash);
}
