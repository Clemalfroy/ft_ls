/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 14:51:07 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 17:05:06 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include "../libft/includes/libft.h"

# define TRUE 1
# define FALSE 0
# define C current
# define BOOL t_bool
# define AG arg

typedef int				t_bool;
typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

typedef struct			s_data
{
	char				*path;
	char				*name;
	t_stat				stat;
	struct s_data		*prev;
	struct s_data		*next;
	BOOL				arg;
}						t_data;

typedef struct			s_env
{
	BOOL				l;
	BOOL				re;
	BOOL				a;
	BOOL				r;
	BOOL				t;
	BOOL				co;
	BOOL				normal;
	int					nbfile;
	DIR					*dir;
}						t_env;

typedef struct			s_inf
{
	int					nbmax;
	int					len_maxgrp;
	int					len_maxowner;
	int					size_max;
	int					total;
}						t_inf;

BOOL					ft_cinstr(const char *str, char c);
t_data					*create_double_list(void);
char					**parse(int argc, char **argv, t_env *env);
void					del_dlist(t_data **lst);
void					dlst_merge(t_data *lst1, t_data *lst2);
void					display_acl(char *fpath);
void					display_link(t_data *current, t_env *env);
void					dlst_del_elem(t_data *element);
void					sort_tab(char **tab, t_env *env, int cpt);
void					display_nb(int nblink, int nbmax);
void					display_file_time(time_t mtime);
void					insert_sorted(t_data *curr, char *ne, t_data *stop,
		t_env *env);
void					clear_dlist(t_data *lst);
void					ft_putfile(t_data *current, t_env *env);
void					dlst_add_after(t_data *element, char *str,
		char *path, int arg);
void					print_major_minor(dev_t st_rdev);
void					affichage_ligne(t_data *current, t_env *env, t_inf
		*info);
void					dlst_add_before(t_data *element, char *str, char *path,
		int arg);
void					display_all(t_data *current, t_data *stop, t_env *env,
		int boo);
extern char				*ft_pathjoin(char const *p1, char const *p2);

#endif
