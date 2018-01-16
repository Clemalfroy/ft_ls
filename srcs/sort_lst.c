/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 17:40:21 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 17:01:44 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		sort_time(char **str)
{
	t_stat	stat1;
	t_stat	stat2;
	int		i;

	i = -1;
	while (str[++i + 1] != NULL)
	{
		stat(str[i], &stat1);
		stat(str[i + 1], &stat2);
		if (stat1.st_mtime < stat2.st_mtime)
		{
			ft_swap(&str[i], &str[i + 1]);
			i = -1;
		}
	}
}

void		sort_alpha(char **tab)
{
	int i;

	i = -1;
	while (tab[++i + 1] != NULL)
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
		{
			ft_swap(&tab[i], &tab[i + 1]);
			i = -1;
		}
	}
}

void		reverse_tab(char **tab, int cpt)
{
	int i;

	i = 0;
	while (i != cpt / 2 + 1)
	{
		ft_swap(&tab[i], &tab[cpt - i]);
		i++;
	}
}

void		sort_file(char **tab)
{
	int		i;
	t_stat	stat1;
	t_stat	stat2;

	i = -1;
	while (tab[++i + 1])
	{
		stat(tab[i], &stat1);
		stat(tab[i + 1], &stat2);
		if (S_ISDIR(stat1.st_mode) && !S_ISDIR(stat2.st_mode))
		{
			ft_swap(&tab[i], &tab[i + 1]);
			i = -1;
		}
	}
}

void		sort_tab(char **tab, t_env *env, int cpt)
{
	sort_alpha(tab);
	if (env->t)
		sort_time(tab);
	if (env->r)
		reverse_tab(tab, cpt);
	sort_file(tab);
}
