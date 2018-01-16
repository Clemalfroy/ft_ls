/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_function2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 11:12:59 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 10:38:57 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		dlst_del_elem(t_data *element)
{
	element->prev->next = element->next;
	element->next->prev = element->prev;
	free(element->path);
	free(element->name);
	free(element);
}

void		dlst_del_firstelem(t_data *racine)
{
	if (racine->next != racine)
		dlst_del_elem(racine->next);
}

void		dlst_del_lasttelem(t_data *racine)
{
	if (racine->prev != racine)
		dlst_del_elem(racine->prev);
}

void		dlst_merge(t_data *lst1, t_data *lst2)
{
	lst1->next->prev = lst2->prev;
	lst2->prev->next = lst1->next;
	lst1->next = lst2;
	lst2->prev = lst1;
}
