/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 06:00:40 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/04 23:01:56 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	str_is_digit(char *s)
{
	int i;

	i = 0;
	while (s[i])
		if (!ft_isdigit(s[i++]))
			return (0);
	return (1);
}

void		ft_exit(char **argv, int *i)
{
	free(g_prompt);
	ft_putstr_fd("exit\n", 1);
	if (!argv)
		exit(0);
	if ((argv[*i + 1] && str_is_digit(argv[*i + 1])
				&& !argv[*i + 2]))
		exit(ft_atoi(argv[*i++ + 1]));
	else if (argv[*i + 1] && !str_is_digit(argv[*i + 1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[*i + 1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(-1);
	}
	else if (argv[*i + 1] && argv[*i + 2] && (g_dollar_quest = 1))
	{
		while (argv[*i + 1])
			(*i)++;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	exit(0);
}
