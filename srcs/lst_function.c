/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 10:08:08 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/04 12:22:14 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_data		*create_double_list(void)
{
	t_data *racine;

	racine = malloc(sizeof(t_data) * 1);
	if (racine != NULL)
	{
		ft_memset(racine, 0, sizeof(t_data));
		racine->next = racine;
		racine->prev = racine;
	}
	return (racine);
}

void		clear_dlist(t_data *lst)
{
	t_data *next;
	t_data *current;

	current = lst->next;
	while (current != lst)
	{
		next = current->next;
		free(current->path);
		free(current->name);
		free(current);
		current = next;
	}
}

void		del_dlist(t_data **lst)
{
	clear_dlist(*lst);
	free(*lst);
	*lst = NULL;
}

void		dlst_add_before(t_data *element, char *str, char *path, int arg)
{
	t_data *new_elem;

	if (element)
	{
		new_elem = malloc(sizeof(t_data));
		if (new_elem != NULL)
		{
			ft_memset(new_elem, 0, sizeof(t_data));
			new_elem->name = ft_strdup(str);
			new_elem->path = ft_strdup(path);
			new_elem->arg = arg;
			lstat(new_elem->path, &new_elem->stat);
			new_elem->prev = element->prev;
			new_elem->next = element;
			element->prev->next = new_elem;
			element->prev = new_elem;
		}
	}
}

void		dlst_add_after(t_data *element, char *str, char *path, int arg)
{
	t_data *new_elem;

	if (element)
	{
		new_elem = malloc(sizeof(t_data));
		if (new_elem != NULL)
		{
			new_elem->name = ft_strdup(str);
			new_elem->path = ft_strdup(path);
			new_elem->arg = arg;
			lstat(new_elem->path, &new_elem->stat);
			new_elem->prev = element;
			new_elem->next = element->next;
			element->next->prev = new_elem;
			element->next = new_elem;
		}
	}
}
