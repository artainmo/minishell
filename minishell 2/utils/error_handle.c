/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 04:50:43 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/01 04:51:54 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_malloc_error(void)
{
	g_error_minishell = 1;
	ft_putstr_fd("Malloc failed shell exit\n", 2);
	exit(0);
}

/*
** Prints error messages for functions that set the errno global variable
*/

void	ft_errno(void)
{
	char *error_message;

	g_error_minishell = 1;
	error_message = strerror(errno);
	ft_putendl_fd(error_message, 2);
}

/*
** Prints a message before the errno err
**  in the format 'minishell: [msg]: [Errnostr]'
*/

void	ft_errnom(char *message)
{
	char *error_message;

	g_error_minishell = 1;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(": ", 2);
	error_message = strerror(errno);
	ft_putendl_fd(error_message, 2);
}

void	ft_errnoq(void)
{
	char *error_message;

	error_message = strerror(errno);
	if (!ft_strcmp(error_message, "Invalid argument")
	&& !ft_strcmp(error_message, "Bad file descriptor"))
	{
		ft_putendl_fd(error_message, 2);
		exit(0);
	}
}
