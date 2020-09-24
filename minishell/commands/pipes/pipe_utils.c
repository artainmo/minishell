/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 06:10:52 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/04 23:24:36 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_not_last_pipes(char *command, t_shell *shell)
{
	int fd_1;

	fd_1 = dup(1);
	close(1);
	ft_shellparsing(command, shell);
	dup2(fd_1, 1);
}

int		pipe_is_last_command_test(char *command)
{
	char	token;
	char	*command_loop;

	command_loop = command;
	while ((token = get_next_redirection_type(command_loop)))
	{
		if (token != '|')
			return (0);
		command_loop = goto_next_redirection(command_loop);
	}
	return (1);
}
