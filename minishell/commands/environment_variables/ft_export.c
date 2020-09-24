/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 07:31:56 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/01 07:32:19 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export(char **commands, int *i, t_shell *shell)
{
	if (!commands[*i + 1])
		env_display(shell->shenvp, 1);
	else
	{
		*i = *i + 1;
		while (commands[*i])
		{
			env_change_value(commands[*i], &shell->shenvp);
			*i = *i + 1;
		}
		*i = *i - 1;
	}
}
