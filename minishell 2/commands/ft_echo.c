/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 05:59:35 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/04 23:03:20 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	put_space_or_linereturn(char **commands, int *i, int *n_flag)
{
	if (commands[*i + 1] && *commands[*i + 1])
	{
		if ((ft_printf(" ")) == -1)
			ft_errnoq();
	}
	else if (!*n_flag)
	{
		if ((ft_printf("\n")) == -1)
			ft_errnoq();
	}
}

static	void	n_flaag(char **commands, int *i, int *n_flag)
{
	*n_flag = 0;
	while (ft_strcmp(commands[*i], "-n"))
	{
		*n_flag = 1;
		*i = *i + 1;
	}
}

void			ft_echo(char **commands, int *i)
{
	int n_flag;

	if (commands[*i + 1])
	{
		*i = *i + 1;
		n_flaag(commands, i, &n_flag);
		while (commands[*i])
		{
			if (ft_printf("%s", commands[*i]) == -1)
				ft_errnoq();
			put_space_or_linereturn(commands, i, &n_flag);
			*i = *i + 1;
		}
		*i = *i - 1;
	}
	else
	{
		if ((ft_printf("\n")) == -1)
			ft_errnoq();
	}
	g_dollar_quest = 0;
}
