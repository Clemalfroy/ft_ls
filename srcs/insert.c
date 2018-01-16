/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 12:45:46 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 17:36:47 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

inline char	*ft_pathjoin(char const *p1, char const *p2)
{
	size_t			l1;
	size_t			l2;
	unsigned char	ds;
	char			*r;

	l1 = ft_strlen(p1);
	if (!(l2 = ft_strlen(p2)) && !l1)
		return (NULL);
	ds = (unsigned char)((!l1 || p1[l1 - 1] != '/') && (!l2 || p2[0] != '/'));
	if (!(r = malloc((l1 + l2 + ds + 1) * sizeof(char))))
		return (NULL);
	if (l1)
		ft_strcpy(r, p1);
	if (ds)
		ft_strcpy(r + l1, "/");
	if (l2)
		ft_strcpy(r + l1 + ds, p2);
	return (r);
}

void		sort_alphab(t_data *current, char *new, t_data *stop, t_env *env)
{
	char	*path;
	int		cp;

	path = ft_pathjoin(current->path, new);
	while (current != stop)
	{
		if (current->next != stop)
			cp = ft_strcmp(new, current->next->name);
		if (current->next == stop || (env->r && cp >= 0) || (!env->r && cp < 0))
		{
			dlst_add_after(current, new, path, FALSE);
			break ;
		}
		current = current->next;
	}
	free(path);
}

void		sort_timeb(t_data *current, char *new, t_data *stop, t_env *env)
{
	char	*path;
	t_stat	stat1;
	int		cp;

	path = ft_pathjoin(current->path, new);
	lstat(path, &stat1);
	while (current != stop)
	{
		if (current->next != stop)
			if (((cp = stat1.st_mtime - current->next->stat.st_mtime) >= 0) &&
			((cp == 0 && ft_strcmp(new, current->next->name) < 0 && !env->r) ||
			(cp == 0 && (ft_strcmp(new, current->next->name) > 0 && env->r))))
			{
				dlst_add_after(current, new, path, FALSE);
				break ;
			}
		if (current->next == stop || (env->r && cp <= 0) || (!env->r && cp > 0))
		{
			dlst_add_after(current, new, path, FALSE);
			break ;
		}
		current = current->next;
	}
	free(path);
}

void		insert_sorted(t_data *current, char *new,
		t_data *stop, t_env *env)
{
	if (env->t)
		sort_timeb(current, new, stop, env);
	else
		sort_alphab(current, new, stop, env);
}
