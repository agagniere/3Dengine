/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 13:32:26 by angagnie          #+#    #+#             */
/*   Updated: 2016/06/05 20:30:29 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system_tree.h"
#include "geometry.h"
#include "ggl.h"

#define POINT(i) (((t_vrtx *)ft_dyna_get(&l, i))->vec.v.c)
#define PROJECT(i) (t_pnt2i){(int)POINT(i).x, (int)POINT(i).z}

int		render(t_env *w)
{
	t_dyna			l;
	t_pnt2i			p[2];
	t_mat4x4		m;
	size_t			i;
	const t_obj		*f = (t_obj *)w->g.world->node.children.root.next;

	ft_bzero(w->pixel,
		w->wdim.d.width * w->wdim.d.height * w->bits_per_pixel / 8);
	ft_putstr("\t--==  Renderin ");
	ft_putstr(f->name);
	ft_putstr("  ==--\n");
	m = mat4_get_transformation((t_gnode *)f);
	l = ft_dyna_new(sizeof(t_vrtx));
	ft_dyna_append(&l, f->vertices.data, f->vertices.chunck_count);
	ft_dyna_iter1(&l, &vrtx_transform, &m);
	i = 0;
	while (i < l.chunck_count)
	{
		if (i % (unsigned)XP(f->dim) < (unsigned)trunc(XP(f->dim) - 1))
		{
			*p = PROJECT(i);
			p[1] = PROJECT(i + 1);
			draw_line(w, p, p + 1);
		}
		if (i / (unsigned)XP(f->dim) < (unsigned)trunc(YP(f->dim) - 1))
		{
			*p = PROJECT(i);
			p[1] = PROJECT(i + (unsigned)XP(f->dim));
			draw_line(w, p, p + 1);
		}
		i++;
	}
	return (0);
}
