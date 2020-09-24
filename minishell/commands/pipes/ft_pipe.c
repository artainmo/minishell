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

static	void	fork_childprocess(char *comm, int fd[2], t_shell *shell)
{
	int		fd1;
	char	**commands;

	close(fd[0]);
	fd1 = dup(1);
	dup2(fd[1], 1);
	if (!(commands = ft_split(comm, ' ')))
		ft_errnoq();
	ft_shellparsing(comm, shell);
	dup2(1, fd1);
	close(fd1);
	close(fd[1]);
	exit(0);
}

static	void	fork_parentprocess(char *comm, int fd[2], t_shell *sh)
{
	int		fd1;
	pid_t	pid;

	if ((pid = fork()) < 0)
	{
		ft_errno();
		exit(0);
	}
	if (!pid)
	{
		close(fd[1]);
		fd1 = dup(0);
		dup2(fd[0], 0);
		ft_shellparsing(comm, sh);
		dup2(0, fd1);
		close(fd1);
		close(fd[0]);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, 0, 0);
}

/*
** Redirecting the stdout of the first command to the stdin
** of the second command
**
** Use the pipe function so that the standard output from one process
** becomes the standard input of the other process
** One process should read from the pipe and the other should write to the pipe
** pipe takes argument int fd[2] with fd[0] for reading and fd[1] for writing
** Returns -1 on error
** Call fork after creating a pipe to connect the parent and child process
** Pipe function is like one kernel you can write and read to it with all
** processes as they keep the same file descriptors
** When not using a fd it needs to be closed from the start.
**
** Use fork to create a child process, the child process contains
** a pid with value zero while the parent process has a positive value.
** By using a if !pid you can use the child process for one specifc action
** and exit the process at end if.
*/

static void		ft_exec_pipe(char *command, char *next_command,
								t_shell *shell)
{
	int		fd[2];
	pid_t	pid;

	g_exec_status = 1;
	if (pipe(fd) == -1)
		ft_errno();
	if ((pid = fork()) < 0)
	{
		ft_errno();
		exit(0);
	}
	if (!pid)
		fork_childprocess(command, fd, shell);
	else
		fork_parentprocess(next_command, fd, shell);
	waitpid(pid, 0, 0);
}

void			ft_pipe(char *command, char *next_command, t_shell *shell)
{
	if (pipe_is_last_command_test(next_command))
		ft_exec_pipe(command, next_command, shell);
	else
	{
		if (!ft_strcmp(command, "sleep 0"))
			g_pipe_buffer = ft_strjoin_f(g_pipe_buffer, command);
		ft_shellparsing(next_command, shell);
	}
}
