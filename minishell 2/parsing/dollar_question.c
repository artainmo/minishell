/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_question.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 07:09:25 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/04 23:28:43 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ultstrcat(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ns;

	i = 0;
	j = 0;
	if (!(ns = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		ft_errnoq();
	while (s1[i])
		ns[i++] = s1[j++];
	free(s1);
	j = 0;
	while (s2[j])
		ns[i++] = s2[j++];
	ns[i] = 0;
	return (ns);
}

void	sub_dq(char **words, int i, int j, char *dq)
{
	char	*part_one;
	char	*tmp;

	if (words[i][j] == '$' && words[i][j + 1] == '?')
	{
		if (!(part_one = ft_substr(words[i], 0, j)))
			ft_errnoq();
		if (!(tmp = ft_substr(words[i], j + 2, ft_strlen(words[i]))))
			ft_errnoq();
		free(words[i]);
		if (!(words[i] = ultstrcat(part_one, dq)))
			ft_errnoq();
		if (!(words[i] = ultstrcat(words[i], tmp)))
			ft_errnoq();
		free(tmp);
	}
}

void	dollar_quest(char **words)
{
	int		i;
	int		j;
	char	*dq;
	t_shell shell;

	if (!(dq = ft_itoa(g_dollar_quest)))
		ft_errnoq();
	i = 1;
	j = 0;
	while (words[i])
	{
		zero_that(&shell.bsq, &shell.bdq, &shell.benc);
		while (words[i][j] && words[i][j + 1])
		{
			if (!shell.benc && !shell.bsq)
				sub_dq(words, i, j, dq);
			toggle_quotesb(words[i][j], &shell);
			j++;
		}
		j = 0;
		i++;
	}
	free(dq);
}
