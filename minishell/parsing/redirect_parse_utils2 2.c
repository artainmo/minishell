/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parse_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 23:32:42 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/04 23:35:29 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Neglect quoted tokens
*/

int		quotes_token_test(char *command, int i)
{
	if (command[i] == '>' || command[i] == '<' || command[i] == '|')
	{
		while (command[i] == ' ')
			i++;
		if (command[i] == '>' || command[i] == '<' || command[i] == '|')
			return (0);
		return (1);
	}
	return (0);
}

/*
** duplicates with malloc the next command before a redirection type
*/

char	*dup_next_redirection(char *command, int *double_flag)
{
	char	*next_command;
	int		i;

	i = 0;
	*double_flag = 0;
	if (command[i] == '>')
	{
		command = command + 1;
		*double_flag = 1;
	}
	while (command[i] != '>' && command[i] != '<'
			&& command[i] != '|' && command[i])
		i++;
	if (!(next_command = ft_substr(command, 0, i)))
		ft_errnoq();
	return (next_command);
}

/*
** Was in c++ comment in f below
** if (command[i + 1] == '>')
**		next_command = &command[i + 2];
**	else
*/

char	*goto_next_redirection(char *command)
{
	char	*next_command;
	int		i;

	i = 0;
	if (!command || !command[i])
		return (0);
	while (command[i + 1] && command[i] != '>' && command[i] != '<'
			&& command[i] != '|')
		i++;
	next_command = &command[i + 1];
	return (next_command);
}

char	get_next_redirection_type(char *command)
{
	int		i;

	i = 0;
	while (command[i] != '>' && command[i] != '<' && command[i] != '|'
			&& command[i])
		i++;
	return (command[i]);
}

int		redinq(char *command)
{
	int		i;
	t_shell	shell;

	i = 0;
	zero_that(&shell.bsq, &shell.bdq, &shell.benc);
	while (command[i])
	{
		if ((command[i] == '<' || command[i] == '>' || command[i] == '|')
				&& (shell.bsq || shell.bdq || shell.benc))
			return (1);
		toggle_quotesb(command[i], &shell);
		i++;
	}
	return (0);
}
