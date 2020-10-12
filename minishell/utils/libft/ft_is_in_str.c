/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_in_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 05:16:34 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/01 05:16:47 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_in_str(char *s, char c)
{
	while (*s)
		if (*s++ == 'c')
			return (1);
	return (0);
}
