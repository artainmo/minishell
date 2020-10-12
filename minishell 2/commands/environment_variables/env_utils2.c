/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 07:27:28 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/01 07:30:38 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**free_prev_str(char **strs, int i)
{
	while (i-- > 0)
	{
		free(strs[i]);
	}
	free(strs);
	return (NULL);
}

/*
** Returns the number of var env
*/

int		n_env(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

int		add_new_env(char ***shenvp, char *env_name, char *new_value)
{
	char	*tmp;
	int		size;

	size = n_env(*shenvp);
	if (!(*shenvp = ft_realloc_dptr(*shenvp, size)))
		return (0);
	if (!(tmp = ft_strjoin(env_name, "=")))
		ft_errnoq();
	free(env_name);
	if (!((*shenvp)[size] = ft_strjoin(tmp, new_value)))
		ft_errnoq();
	free(tmp);
	return (1);
}

/*
** Decrease the number of char * in your char **
** First char * == NULL gets removed
*/

char	**ft_sralloc_dptr(char **ptr, int size)
{
	int		i;
	int		j;
	char	**new_ptr;

	if (!(new_ptr = malloc(sizeof(char *) * (size))))
		ft_errnoq();
	i = 0;
	j = 0;
	while (i < size)
	{
		if (!ptr[i])
		{
			i++;
			continue;
		}
		if (!(new_ptr[j] = ft_strdup(ptr[i])))
			return (free_prev_str(new_ptr, j));
		free(ptr[i]);
		i++;
		j++;
	}
	new_ptr[j] = NULL;
	free(ptr);
	return (new_ptr);
}
