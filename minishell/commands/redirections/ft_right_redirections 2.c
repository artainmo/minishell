/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_right_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 07:48:20 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/04 23:23:07 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** https://catonmat.net/bash-one-liners-explained-part-three
** redirect the standard output of a command to a file
** (that does or does not exist yet)
** (if file already exists it deletes prior content to put the new content
** inside it),  same as command 1 > file (because one is standard
** output file descriptor)
** command 2 > file, 2 stands for stderr, all errors returns are
** written inside the file
** command &>file, both standard output and strerr are written to the file
*/

/*
** Some file descriptors are by default used for
** standard streams: stdin, stdout, stderr
** stdin has file descriptor 0, this reffers to what you are writing/typing
** in the terminal, when reading from terminal get_next_line
** uses file descriptor 0 stdout has file descriptor 1,
** this refers to what has been written
** in the terminal as valid output function write and printf write
** on file descriptor 1 usually
** stderr has file descriptor 2,
** this refers to what has been written in the terminal as
** non-valid input or error messages (generated through errno)
*/

static	void	ft_stdout(char *command, int fd, char *filename, t_shell *sh)
{
	int fd_1;

	fd_1 = dup(1);
	dup2(fd, 1);
	ft_shellparsing(command, sh);
	if (g_error_minishell)
	{
		if (!(open(filename, O_TRUNC, 0666)))
			ft_errno();
		g_error_minishell = 0;
	}
	dup2(fd_1, 1);
	free(filename);
	close(fd_1);
	close(fd);
}

static	char	*double_flag_set_loop(char *loop, int double_flag)
{
	if (loop[0] == '>')
		return (loop + 1);
	else if (double_flag)
		return (loop + 1);
	return (loop);
}

char			*ft_set_right_redir_pipe(char *next_cmd)
{
	int i;

	i = 0;
	while (next_cmd[i] && next_cmd[i] != '|')
		i++;
	if (!(next_cmd = ft_strjoin("sleep 0", &next_cmd[i])))
		ft_errnoq();
	return (next_cmd);
}

/*
** LEGACY CODE (only works on macos), at eof: free(real_cmd);
*/

static void		ft_right_redirec2(char *command, char **comm_loop,
									int error, t_shell *shell)
{
	char	*real_cmd;
	char	*loop;
	int		last;

	last = ft_count_words(comm_loop) - 1;
	loop = shell->norm_right_redirec_loop;
	if (!shell->right_left)
		real_cmd = mright_redir_parse(comm_loop);
	else
		real_cmd = command;
	if (!error)
		ft_stdout(real_cmd, right_open_fd(comm_loop[last], shell, error)
		, get_filename_no_spaces(comm_loop[last]), shell);
	if (get_next_redirection_type(loop) == '|' && !shell->right_left)
	{
		loop = ft_set_right_redir_pipe(loop);
		ft_shellparsing(loop, shell);
		free(loop);
	}
	else if (get_next_redirection_type(loop) && !shell->right_left)
		ft_shellparsing(loop, shell);
	double_str_free(comm_loop);
}

void			ft_right_redirection(char *command, char *loop, t_shell *shell)
{
	int		fd;
	int		i;
	char	**comloop;
	int		error;

	i = 0;
	error = 0;
	if (!(comloop = malloc(sizeof(char *) * (comm_red_lenght(loop, '>') + 2))))
		ft_errnoq();
	comloop[i++] = ft_strdup(command);
	comloop[i++] = dup_next_redirection(loop, &shell->double_rflag);
	if ((fd = right_open_fd(comloop[i - 1], shell, error)) == -1)
		error = 1;
	loop = double_flag_set_loop(loop, 0);
	while (get_next_redirection_type(loop) == '>')
	{
		loop = goto_next_redirection(loop);
		comloop[i] = dup_next_redirection(loop, &shell->double_rflag);
		loop = double_flag_set_loop(loop, shell->double_rflag);
		if ((fd = right_open_fd(comloop[i++], shell, error)) == -1)
			error = 1;
	}
	comloop[i] = 0;
	shell->norm_right_redirec_loop = loop;
	ft_right_redirec2(command, comloop, error, shell);
}
