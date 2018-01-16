/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 14:22:06 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 16:15:51 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		display_type(mode_t st_mode)
{
	if ((S_ISFIFO(st_mode)))
		ft_putstr("p");
	else if ((S_ISCHR(st_mode)))
		ft_putstr("c");
	else if ((S_ISDIR(st_mode)))
		ft_putstr("d");
	else if ((S_ISBLK(st_mode)))
		ft_putstr("b");
	else if ((S_ISREG(st_mode)))
		ft_putstr("-");
	else if ((S_ISLNK(st_mode)))
		ft_putstr("l");
	else if ((S_ISSOCK(st_mode)))
		ft_putstr("s");
	else
		ft_putstr(" ");
}

void		display_rights(mode_t st_mode)
{
	char *ret;

	ret = ft_strnew(10);
	ret[0] = ((st_mode & S_IRUSR) ? 'r' : '-');
	ret[1] = ((st_mode & S_IWUSR) ? 'w' : '-');
	ret[2] = ((st_mode & S_IXUSR) ? 'x' : '-');
	ret[2] = ((st_mode & S_ISUID) ? 'S' : ret[2]);
	ret[2] = (ret[2] == 'S' && (st_mode & S_IXUSR) ? 's' : ret[2]);
	ret[3] = ((st_mode & S_IRGRP) ? 'r' : '-');
	ret[4] = ((st_mode & S_IWGRP) ? 'w' : '-');
	ret[5] = ((st_mode & S_IXGRP) ? 'x' : '-');
	ret[5] = ((st_mode & S_ISGID) ? 'S' : ret[5]);
	ret[5] = (ret[5] == 'S' && (st_mode & S_IXGRP) ? 's' : ret[5]);
	ret[6] = ((st_mode & S_IROTH) ? 'r' : '-');
	ret[7] = ((st_mode & S_IWOTH) ? 'w' : '-');
	ret[8] = ((st_mode & S_IXOTH) ? 'x' : '-');
	ret[8] = ((st_mode & S_ISVTX) ? 'T' : ret[8]);
	ret[8] = (ret[8] == 'T' && (st_mode & S_IXOTH) ? 't' : ret[8]);
	ft_putstr(ret);
	ft_strdel(&ret);
}

void		display_file_owner(uid_t st_uid, t_inf *info)
{
	struct passwd	*pass;
	int				i;

	i = -1;
	if ((pass = getpwuid(st_uid)) != NULL)
		;
	else
		pass->pw_name = ft_itoa(st_uid);
	ft_putstr(pass->pw_name);
	if (info->len_maxowner >= (int)ft_strlen(pass->pw_name))
		while (++i != (int)(info->len_maxowner - ft_strlen(pass->pw_name)))
			ft_putchar(' ');
}

void		display_file_group(gid_t gid, t_inf *info)
{
	struct group	*grp;
	int				i;

	i = -1;
	if ((grp = getgrgid(gid)) != NULL)
		;
	else
		grp->gr_name = ft_itoa(gid);
	ft_putstr(grp->gr_name);
	if (info->len_maxgrp >= (int)ft_strlen(grp->gr_name))
		while (++i != (int)(info->len_maxgrp - ft_strlen(grp->gr_name)))
			ft_putchar(' ');
}

void		affichage_ligne(t_data *current, t_env *env, t_inf *info)
{
	display_type(current->stat.st_mode);
	display_rights(current->stat.st_mode);
	display_acl(current->path);
	ft_putstr(" ");
	display_nb(current->stat.st_nlink, info->nbmax);
	ft_putstr(" ");
	display_file_owner(current->stat.st_uid, info);
	ft_putstr("  ");
	display_file_group(current->stat.st_gid, info);
	ft_putstr("  ");
	if (S_ISCHR(current->stat.st_mode) || S_ISBLK(current->stat.st_mode))
		print_major_minor(current->stat.st_rdev);
	else
		display_nb(current->stat.st_size, info->size_max);
	ft_putchar(' ');
	display_file_time(current->stat.st_mtime);
	ft_putchar(' ');
	if (!S_ISLNK(current->stat.st_mode))
	{
		ft_putfile(current, env);
		ft_putchar('\n');
	}
	else
		display_link(current, env);
}
