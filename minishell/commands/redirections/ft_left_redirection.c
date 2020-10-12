/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_left_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 07:43:43 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/04 23:07:20 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
**  < It redirects the file after < to stdin of the program before <
**
** << ./a 0 << FIN write in stdin what you want until FIN is reached,
** once FIN is reached you cannot write in stdin anymore
** and the program is executed
*/

static void		ft_left_exec(char *command, int fd, t_shell *shell)
{
	int		fd_1;

	fd_1 = dup(0);
	dup2(fd, 0);
	ft_shellparsing(command, shell);
	dup2(fd_1, 0);
	close(fd_1);
}

static char		*ft_set_left_redir_pipe(char *cmd, char *next_cmd)
{
	int		i;
	char	*new_comm;

	i = 0;
	while (next_cmd[i] != '|')
		i++;
	next_cmd[i] = '\0';
	if (!(new_comm = ft_strjoin("cat ", next_cmd)))
		ft_errnoq();
	if (!(new_comm = ft_strjoin_f(new_comm, "|")))
		ft_errnoq();
	if (!(new_comm = ft_strjoin_f(new_comm, cmd)))
		ft_errnoq();
	if (!(new_comm = ft_strjoin_f(new_comm, "|")))
		ft_errnoq();
	if (!(new_comm = ft_strjoin_f(new_comm, &next_cmd[i + 1])))
		ft_errnoq();
	return (new_comm);
}

static void		ft_left_redirec2(char *loop, char *cmd, int error, t_shell *sh)
{
	if (get_next_redirection_type(loop) == '|'
		&& !error && !ft_strchr(loop, '<'))
	{
		loop = ft_set_left_redir_pipe(cmd, loop);
		ft_shellparsing(loop, sh);
		free(loop);
	}
	else if (error && get_next_redirection_type(loop))
	{
		loop = ft_set_right_redir_pipe(loop);
		ft_shellparsing(loop, sh);
		free(loop);
	}
	else if (get_next_redirection_type(loop))
		ft_shellparsing(loop, sh);
}

/*
** Tries to open all the fds that come after the first command, if he cannot
** open it because it does not exist it returns an error and does not execute
** in the end. If no error it takes the last file or redirection to execute
** with first command.
*/

void			ft_left_redirection(char *cmd, char *next_cmd, t_shell *sh)
{
	int		fd;
	char	*loop;
	int		error;
	int		bl;

	error = 0;
	loop = next_cmd;
	if ((fd = left_open_fd(dup_next_redirection(loop, &bl), error)) == -1)
		error = 1;
	while (get_next_redirection_type(loop) == '<')
	{
		loop = goto_next_redirection(loop);
		if ((fd = left_open_fd(dup_next_redirection(loop, &bl), error)) == -1)
			error = 1;
	}
	if (!error && !ft_strchr(loop, '<')
		&& get_next_redirection_type(loop) != '|')
		ft_left_exec(cmd, fd, sh);
	ft_left_redirec2(loop, cmd, error, sh);
}
