/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 07:55:11 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/02 17:26:28 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char			*parse_rightredirection_type(char *command)
{
	int i;

	i = 0;
	while (command && command[i] && command[i] != '>')
		i++;
	if (command[i] == '>')
	{
		command = command + 1;
		return ("double_right");
	}
	else
		return ("right");
}

char			*get_filename_no_spaces(char *filename)
{
	int		i;
	int		d_f;
	char	*new_filename;
	char	*tmp;

	i = 0;
	tmp = dup_next_redirection(filename, &d_f);
	if (!(new_filename = ft_strtrim(tmp, " ")))
		ft_errnoq();
	free(tmp);
	while (new_filename[i] && new_filename[i] != ' ')
		i++;
	new_filename[i] = '\0';
	return (new_filename);
}

int				right_open_fd(char *command, t_shell *shell, int error)
{
	int		fd;
	char	*filename;

	fd = 0;
	filename = get_filename_no_spaces(command);
	if (!shell->double_rflag && !error)
	{
		if ((fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0666)) == -1)
			ft_errnom(filename);
	}
	else if (shell->double_rflag && !error)
	{
		if ((fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0666)) == -1)
			ft_errnom(filename);
	}
	free(filename);
	return (fd);
}

int				left_open_fd(char *command, int error)
{
	int		fd;
	char	*filename;

	filename = get_filename_no_spaces(command);
	fd = 0;
	if (!error)
	{
		if ((fd = open(filename, O_RDONLY, 0666)) == -1)
			ft_errnom(filename);
	}
	free(filename);
	free(command);
	return (fd);
}

char			**split_redirection_commands(char *command)
{
	char	*type;
	char	**commands_betw_redirec;

	type = parse_rightredirection_type(command);
	if (ft_strcmp(type, "right") || ft_strcmp(type, "double_right"))
	{
		if (!(commands_betw_redirec = ft_split(command, '>')))
			ft_errnoq();
	}
	else
	{
		if (!(commands_betw_redirec = ft_split(command, '<')))
			ft_errnoq();
	}
	return (commands_betw_redirec);
}
