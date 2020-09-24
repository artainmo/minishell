/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_left_redirect_only.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:27:26 by sel-melc          #+#    #+#             */
/*   Updated: 2020/03/09 15:27:32 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static	int	is_redirect(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

/*
** Returns 0 if there was a double left redirection followed
*/

int			double_lredirect_only(char *s)
{
	int i;
	int dr;
	int r;

	i = 0;
	dr = 0;
	r = 0;
	while (s[i])
	{
		if (s[i + 1] && s[i] == '<'
			&& s[i + 1] == '<' && r)
			return (0);
		if (s[i] == ';' && !(r = 0))
			dr = 0;
		if (s[i + 1] && s[i] == '<'
			&& s[i + 1] == '<' && (++i))
			dr = 1;
		else if (is_redirect(s[i]) && dr)
			return (0);
		else if (is_redirect(s[i]))
			r = 1;
		i++;
	}
	return (1);
}
