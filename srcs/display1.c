/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 11:06:40 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 17:00:18 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_putfile(t_data *current, t_env *env)
{
	if (env->co)
	{
		if (S_ISDIR(current->stat.st_mode))
			ft_putstr_cyan(current->name);
		else if (S_ISLNK(current->stat.st_mode))
			ft_putstr_pink(current->name);
		else if (S_ISCHR(current->stat.st_mode))
			ft_spr_putstr("\033[34m\033[43m", current->name, "\033", "[0m");
		else if (S_ISSOCK(current->stat.st_mode))
			ft_putstr_green(current->name);
		else if (current->stat.st_mode & S_IXUSR)
			ft_putstr_red(current->name);
		else
			ft_putstr(current->name);
	}
	else
		ft_putstr(current->name);
}

void		get_info(t_inf *info, t_data *current, t_data *stop, int boo)
{
	struct group	*grp;
	struct passwd	*pass;

	while (current != stop && (info->total += current->stat.st_blocks) >= 0)
	{
		if ((grp = getgrgid(current->stat.st_gid)) != NULL)
			;
		else
			grp->gr_name = ft_itoa(current->stat.st_gid);
		if ((pass = getpwuid(current->stat.st_uid)) != NULL)
			;
		else
			pass->pw_name = ft_itoa(current->stat.st_uid);
		info->nbmax = ft_nblen(current->stat.st_nlink) > info->nbmax ?
			ft_nblen(current->stat.st_nlink) : info->nbmax;
		info->size_max = ft_nblen(current->stat.st_size) > info->size_max ?
			ft_nblen(current->stat.st_size) : info->size_max;
		current = current->next;
		info->len_maxgrp = (int)ft_strlen(grp->gr_name) > info->len_maxgrp ?
			ft_strlen(grp->gr_name) : info->len_maxgrp;
		info->len_maxowner = (int)ft_strlen(pass->pw_name) > info->len_maxowner
			? ft_strlen(pass->pw_name) : info->len_maxowner;
	}
	if (boo)
		ft_spr_putstr("total ", ft_itoa(info->total), "\n", "");
}

int			get_size(t_data *current, t_data *stop)
{
	size_t value;

	value = 0;
	while (current != stop)
	{
		if (ft_strlen(current->name) > value)
			value = ft_strlen(current->name);
		current = current->next;
	}
	return (value);
}

void		display_aligned(t_data *current, t_env *env, t_data *stop)
{
	ft_putfile(current, env);
	if (current->next == stop)
		ft_putchar('\n');
	else
		ft_putstr(" \t");
}

void		display_all(t_data *current, t_data *stop, t_env *env, int boo)
{
	t_inf info;

	ft_memset(&info, 0, sizeof(t_inf));
	if (boo == TRUE)
		current = current->next;
	if (env->l && current != stop)
		get_info(&info, current, stop, boo);
	while (current != stop)
	{
		if (env->l)
			affichage_ligne(current, env, &info);
		else if (env->normal == TRUE)
		{
			ft_putfile(current, env);
			ft_putchar('\n');
		}
		else
			display_aligned(current, env, stop);
		if (!S_ISDIR(current->stat.st_mode) || ft_strcmp(current->name, ".")
				== 0 || ft_strcmp(current->name, "..") == 0)
			dlst_del_elem(current);
		current = current->next;
	}
}
