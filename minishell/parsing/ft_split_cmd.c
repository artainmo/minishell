/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:30:45 by artainmo          #+#    #+#             */
/*   Updated: 2019/10/21 22:10:30 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_freesplit(char **str)
{
	int i;

	i = 0;
	free(str);
	while (str[i])
	{
		free(str[i]);
		i++;
	}
}

static int	ft_isnum(char a, char b)
{
	return (a == b);
}

static int	ft_count(char const *s, char c, t_shell *shell)
{
	int		i;
	int		counter;
	int		new_str;

	i = 0;
	counter = 0;
	new_str = 1;
	while (s[i])
	{
		if (!(ft_isnum(s[i], c)) && !shell->bsq
			&& !shell->bdq && !shell->benc && new_str)
		{
			counter++;
			new_str = 0;
		}
		if (ft_isnum(s[i], c))
			new_str = 1;
		toggle_quotesb(c, shell);
		i++;
	}
	counter++;
	return (counter);
}

static char	*ft_next_substr(char const *s, char c, int *l, t_shell *sh)
{
	int	sub_str_start;
	int sub_str_size;

	while (s[*l] == c)
		*l = *l + 1;
	sub_str_start = *l;
	while (s[*l])
	{
		if (*l > 0 && !sh->benc
			&& !sh->bsq && !sh->bdq && s[*l] == c)
			break ;
		toggle_quotesb(s[*l], sh);
		*l = *l + 1;
	}
	zero_that(&sh->bsq, &sh->bdq, &sh->benc);
	sub_str_size = *l - sub_str_start;
	return (ft_substr(s, sub_str_start, sub_str_size));
}

char		**ft_split_cmd(char const *s, char c)
{
	int		counter;
	char	**str;
	int		i;
	int		l;
	t_shell	shell;

	zero_that(&shell.bsq, &shell.bdq, &shell.benc);
	if ((i = -1) &&
		!(l = 0) && s == NULL)
		return (0);
	counter = ft_count(s, c, &shell);
	if (!(str = malloc(sizeof(char*) * (counter))))
		return (0);
	while (counter != 1)
	{
		str[++i] = ft_next_substr(s, c, &l, &shell);
		if (!str[i])
		{
			ft_freesplit(str);
			return (str);
		}
		counter--;
	}
	str[++i] = 0;
	return (str);
}
