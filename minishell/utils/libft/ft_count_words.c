/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 18:06:13 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/01 05:18:07 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(char **double_str)
{
	int i;

	i = 0;
	if (!double_str)
		return (0);
	while (double_str[i])
		i++;
	return (i);
}
