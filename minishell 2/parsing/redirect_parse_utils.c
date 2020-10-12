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

int			if_double_right(char *str, int *i)
{
	*i = *i + 1;
	if (str[*i] == '>')
		return (1);
	*i = *i - 1;
	return (0);
}

static char	*right_left_redirection_parse(char *command, char **next_command)
{
	char	*command_loop;
	int		i;

	i = 0;
	command_loop = command;
	while (get_next_redirection_type(command_loop) == '>')
		command_loop = goto_next_redirection(command_loop);
	if (get_next_redirection_type(command_loop) == '<')
	{
		while (command[i] && command[i] != '|')
			i++;
		if (command[i] == '|')
		{
			if (!(*next_command = &command[i]))
				ft_errnoq();
			*next_command = ft_set_right_redir_pipe(*next_command);
		}
		else
			next_command = 0;
		command[i] = '\0';
		return (command);
	}
	return (0);
}

static char	*left_right_redirection_parse(char *command, char **next_command)
{
	char	*command_loop;
	int		i;

	i = 0;
	command_loop = command;
	while (get_next_redirection_type(command_loop) == '<')
		command_loop = goto_next_redirection(command_loop);
	if (get_next_redirection_type(command_loop) == '>')
	{
		while (command[i] && command[i] != '|')
			i++;
		if (command[i] == '|')
		{
			if (!(*next_command = &command[i]))
				ft_errnoq();
			*next_command = ft_set_right_redir_pipe(*next_command);
		}
		else
			next_command = 0;
		command[i] = '\0';
		return (command);
	}
	return (0);
}

char		*ft_left_right_redirection_parse(char *command, char **next_command)
{
	if (get_next_redirection_type(command) == '>')
		return (right_left_redirection_parse(command, next_command));
	else if (get_next_redirection_type(command) == '<')
		return (left_right_redirection_parse(command, next_command));
	return (0);
}

char		next_redirection(char *command, char **next_command, t_shell *shell)
{
	char *pointer_to_redirec;
	char *chars;
	char redirec_type;

	if (!(chars = malloc(3)))
		ft_errnoq();
	chars[0] = '>';
	chars[1] = '<';
	chars[2] = '|';
	if ((pointer_to_redirec = ft_strchr_wquotes(command, chars, *shell)))
	{
		redirec_type = *pointer_to_redirec;
		*pointer_to_redirec = '\0';
		*next_command = pointer_to_redirec + 1;
		if (*next_command[0] == '<')
			redirec_type = 'l';
		else
			*pointer_to_redirec = '\0';
	}
	else
		redirec_type = 0;
	free(chars);
	return (redirec_type);
}
