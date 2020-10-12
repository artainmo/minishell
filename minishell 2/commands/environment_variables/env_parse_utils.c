/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 08:07:11 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/01 08:07:40 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	toggle_bool(t_shell *shell, char *env_split, int j)
{
	while (env_split[j])
	{
		if (env_split[j] == '\'')
			shell->bsq = (!shell->bsq) ? 1 : 0;
		else if (env_split[j] == '\\')
			shell->benc = (!shell->benc) ? 1 : 0;
		j++;
	}
	return (j);
}
