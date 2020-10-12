/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 07:41:40 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/01 07:42:18 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	splitlen(char **split)
{
	int i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	free_split(char **split, char *str)
{
	int i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	free(str);
	return (1);
}

int	wexitstatus(int status)
{
	return (((*(int *)&(status)) >> 8) & 0x000000ff);
}

int	norm_free(char **s)
{
	free_split(s, 0);
	return (1);
}
