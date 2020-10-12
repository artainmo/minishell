/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 07:32:45 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/01 07:33:28 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(char **commands, int *i, t_shell *shell)
{
	if (!commands[*i + 1])
		ft_putstr_fd("unset: not enough arguments\n", 2);
	else
	{
		*i = *i + 1;
		while (commands[*i])
		{
			unset(commands[*i], &shell->shenvp);
			*i = *i + 1;
		}
		*i = *i - 1;
	}
	g_dollar_quest = 0;
}
