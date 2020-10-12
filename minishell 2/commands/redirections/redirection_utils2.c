/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 07:59:46 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/01 08:03:11 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	char	*begin_comm_no_status(char *comm, int comm_stat_ind)
{
	char	*begin_comm;

	if (!(begin_comm = ft_substr(comm, 0, comm_stat_ind)))
		ft_errnoq();
	free(comm);
	return (begin_comm);
}

/*
** Returns -1 if command status not found otherwise it returns the index
** where the command status was found
*/

static	char	test_comm_status(char *comm, char test)
{
	int	i;
	int	remember_location;

	remember_location = -1;
	if ((i = ft_strrchr_m(comm, test)) != -1)
	{
		remember_location = i;
		if (comm[i + 1] || comm[i - 1] != ' ')
			remember_location = -1;
	}
	return (remember_location);
}

int				get_command_status(char *command)
{
	if ((test_comm_status(command, '1')) != -1)
		return ('1');
	if ((test_comm_status(command, '2')) != -1)
		return ('2');
	if ((test_comm_status(command, '&')) != -1)
		return ('&');
	return ('0');
}

char			*get_begin_comm(char *command)
{
	int		comm_stat_ind;
	char	*begin_comm;

	if ((comm_stat_ind = test_comm_status(command, '1')) != -1)
		return (begin_comm_no_status(command, comm_stat_ind));
	if ((comm_stat_ind = test_comm_status(command, '2')) != -1)
		return (begin_comm_no_status(command, comm_stat_ind));
	if ((comm_stat_ind = test_comm_status(command, '&')) != -1)
		return (begin_comm_no_status(command, comm_stat_ind));
	if (!(begin_comm = ft_strdup(command)))
		ft_errno();
	free(command);
	return (begin_comm);
}
