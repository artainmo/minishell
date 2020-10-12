/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 07:34:15 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/02 09:55:30 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void			cat_file(char *executable)
{
	int		fd;
	int		ret;
	char	*line;

	if ((fd = open(executable, O_RDONLY)) == -1)
		ft_errno();
	else
	{
		while ((ret = get_next_line(fd, &line)))
		{
			if (ret == -1)
				ft_errno();
			if ((ft_printf("%s\n", line)) == -1)
				ft_errnoq();
			free(line);
		}
		close(fd);
	}
}

void			ft_exec_cat(char **commands, int *i)
{
	*i = *i + 1;
	while (commands[*i])
	{
		cat_file(commands[*i]);
		*i = *i + 1;
	}
	*i = *i - 1;
}
