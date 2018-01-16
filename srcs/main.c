/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:04:59 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 17:22:24 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_data		*create_lst(int argc, char **argv, t_env *env)
{
	char	**tab;
	int		i;
	t_data	*lst;

	i = -1;
	tab = parse(argc, argv, env);
	if (!tab[0])
		exit(1);
	lst = create_double_list();
	while (tab[++i])
		dlst_add_before(lst, tab[i], tab[i], TRUE);
	free(tab);
	return (lst);
}

void		print_error(char *str)
{
	ft_putstr_fd("./ft_ls: ", 2);
	perror(str);
	ft_putstr_fd("\n", 2);
}

void		compute_directory(t_data *current, t_env *env, t_data *root)
{
	t_dirent	*data;
	t_data		*stop;

	if (C->arg == TRUE || (env->re && ft_strcmp(C->name, ".") != 0 &&
				ft_strcmp(C->name, "..") != 0))
	{
		if (C->arg == FALSE || env->nbfile > 1)
			ft_spr_putstr(C->path, ":", "\n", "");
		if ((env->dir = opendir(C->path)) == NULL)
			print_error(C->name);
		else
		{
			stop = C->next;
			while ((data = readdir(env->dir)) != NULL)
				if (data->d_name[0] == '.' && !env->a)
					;
				else
					insert_sorted(C, data->d_name, stop, env);
			display_all(C, stop, env, TRUE);
			if (C->next != root)
				if (!ft_cinstr(C->next->path, '/') || env->re || root->prev->AG)
					ft_putchar('\n');
			closedir(env->dir);
		}
	}
}

BOOL		check_link(t_data *lst)
{
	char	*result;
	int		ret;
	t_stat	stat1;

	if (!S_ISLNK(lst->stat.st_mode))
		return (0);
	result = malloc(sizeof(char) * 4096);
	ret = readlink(lst->path, result, 4096);
	result[ret] = 0;
	stat(result, &stat1);
	if (!S_ISDIR(stat1.st_mode))
		return (0);
	free(result);
	return (1);
}

int			main(int argc, char **argv)
{
	t_env		env;
	t_data		*lst;
	t_data		*cpy;

	ft_memset(&env, 0, sizeof(t_env));
	lst = create_lst(argc, argv, &env);
	cpy = lst->next;
	while (cpy != lst)
	{
		if (S_ISDIR(cpy->stat.st_mode) || check_link(cpy))
			compute_directory(cpy, &env, lst);
		else if (cpy->arg == TRUE)
		{
			if (env.l)
				display_all(cpy, cpy->next, &env, FALSE);
			else
				ft_putendl(cpy->name);
			if (S_ISDIR(cpy->next->stat.st_mode))
				ft_putstr("\n");
		}
		cpy = cpy->next;
	}
	del_dlist(&lst);
	return (1);
}
