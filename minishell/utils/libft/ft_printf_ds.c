/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 05:08:49 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/01 05:09:18 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_ds(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_putendl_fd(str[i], 1);
		i++;
	}
}
