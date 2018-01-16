/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:08:21 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 17:01:49 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

BOOL		ft_cinstr(const char *str, char c)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (TRUE);
	return (FALSE);
}

BOOL		check_existence(char **file, char *file1)
{
	t_stat	stat;
	int		i;

	i = -1;
	while (file[++i])
	{
		if (ft_strcmp(file[i], "") == 0)
		{
			ft_putstr_fd("./ft_ls: fts_open: No such file or directory\n", 2);
			exit(1);
		}
	}
	if (lstat(file1, &stat) == -1)
	{
		ft_putstr_fd("ft_ls: ", 2);
		perror(file1);
		return (FALSE);
	}
	return (TRUE);
}

void		test(char *str)
{
	int i;

	i = -1;
	if (ft_strstr(str, "--"))
	{
		ft_putstr_fd("ft_ls: illegal option -- -", 2);
		ft_putendl_fd("\nusage: ft_ls [-rlaRtG19] [file ...]", 2);
		exit(1);
	}
	while (str[++i])
		if (ft_cinstr("-rlaRtG19", str[i]) == FALSE && !(str[i + 1] = '\0'))
		{
			ft_putstr_fd("ft_ls: illegal option -- ", 2);
			ft_putstr_fd(&str[i], 2);
			ft_putendl_fd("\nusage: ft_ls [-rlaRtG19] [file ...]", 2);
			exit(1);
		}
}

void		test_flag(char *str, t_env *env)
{
	env->normal = TRUE;
	if (ft_cinstr(str, 'r') == TRUE)
		env->r = TRUE;
	if (ft_cinstr(str, 'l') == TRUE)
		env->l = TRUE;
	if (ft_cinstr(str, 'a') == TRUE)
		env->a = TRUE;
	if (ft_cinstr(str, 'R') == TRUE)
		env->re = TRUE;
	if (ft_cinstr(str, 't') == TRUE)
		env->t = TRUE;
	if (ft_cinstr(str, 'G') == TRUE)
		env->co = TRUE;
	if (ft_cinstr(str, '1') == TRUE)
		env->normal = TRUE;
	if (ft_cinstr(str, '9') == TRUE)
		env->normal = FALSE;
	test(str);
}

int		g_c[3] = {FALSE, -1, 0};

char		**parse(int argc, char **a, t_env *env)
{
	char	**tab;

	if ((tab = malloc(sizeof(char **) * argc + 1)) == NULL)
		return (NULL);
	tab[0] = NULL;
	while (++g_c[2] < argc)
	{
		if (ft_strequ("--", a[g_c[2]]) == TRUE && g_c[0] == FALSE && ++g_c[2])
			g_c[0] = TRUE;
		if (g_c[0] == FALSE && a[g_c[2]][0] == '-' && ft_strlen(a[g_c[2]]) > 1)
			test_flag(a[g_c[2]], env);
		else
		{
			if (a[g_c[2]] && ++env->nbfile)
			{
				sort_tab(&a[g_c[2]], env, 0);
				if (check_existence(a, a[g_c[2]]) && (g_c[0] = TRUE))
					tab[++g_c[1]] = a[g_c[2]];
			}
		}
	}
	env->nbfile == 0 ? tab[++g_c[1]] = ".\0" : 0;
	if (tab[0] != NULL && !(tab[++g_c[1]] = NULL))
		sort_tab(tab, env, g_c[1] - 1);
	return (tab);
}
