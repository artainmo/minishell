/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 21:27:23 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/01 04:52:17 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../../minishell.h"

int		get_next_line(int fd, char **line)
{
	static char		buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	int				ret;
	int				i;

	i = 0;
	ret = 1;
	if (BUFFER_SIZE < 1 || !line || (!(*line = ft_strjoin_m(NULL, buffer[fd]))))
		return (-1);
	while (ft_strchr_m(buffer[fd], '\n') == -1 && (ret || **line))
	{
		if ((ret = read(fd, buffer[fd], BUFFER_SIZE)) == -1)
			return (-1);
		buffer[fd][ret] = '\0';
		if (ret == 0)
			g_ctrl_d = 1;
		if (!(*line = ft_strjoin_m(*line, buffer[fd])))
			return (-1);
	}
	ret = ft_strchr_m(buffer[fd], '\n') + 1;
	if (buffer[fd][0] == '\0')
		return (0);
	while (buffer[fd][ret] != '\0')
		buffer[fd][i++] = buffer[fd][ret++];
	buffer[fd][i] = '\0';
	return (1);
}
