/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_line2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 14:56:28 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 17:00:33 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_major_minor(dev_t st_rdev)
{
	ft_putnbr(major(st_rdev));
	ft_putstr(", ");
	ft_putnbr(minor(st_rdev));
}

void		display_file_time(time_t mtime)
{
	char		*tmp;
	time_t		now;

	now = time(0);
	tmp = ft_strdup(ctime(&mtime));
	write(1, tmp + 4, 7);
	if (mtime > now)
		ft_putstr(" 10000");
	else if (now - mtime > 15778463)
	{
		ft_putchar(' ');
		write(1, tmp + 20, 4);
	}
	else
		write(1, tmp + 11, 5);
	ft_strdel(&tmp);
}

void		display_nb(int nblink, int nbmax)
{
	int i;

	i = -1;
	while (++i != nbmax - ft_nblen(nblink))
		ft_putchar(' ');
	ft_putnbr(nblink);
}

void		display_link(t_data *current, t_env *env)
{
	char	*result;
	int		ret;

	result = malloc(sizeof(char) * 4096);
	ret = readlink(current->path, result, 4096);
	result[ret] = 0;
	if (env->co)
		ft_putstr_pink(current->name);
	else
		ft_putstr(current->name);
	ft_spr_putstr("", " -> ", result, "\n");
	ft_strdel(&result);
}

void		display_acl(char *fpath)
{
	int		xattrs;
	acl_t	acl;

	xattrs = (int)listxattr(fpath, NULL, 1, XATTR_NOFOLLOW);
	if (xattrs > 0)
		ft_putchar('@');
	else
	{
		acl = acl_get_file(fpath, ACL_TYPE_EXTENDED);
		if (acl != NULL)
			ft_putchar('+');
		else
			ft_putchar(' ');
	}
}
