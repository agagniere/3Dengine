/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ggl_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 12:36:43 by angagnie          #+#    #+#             */
/*   Updated: 2016/04/27 06:02:54 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ggl.h"

static void		destroy_env(t_env *const w)
{
	mlx_destroy_image(w->mlx, w->img);
	mlx_destroy_window(w->mlx, w->win);
	ft_putstr("  --==  Clear  ==--\n");
}

static int		init_env(t_env *const w)
{
	w->fnct.repaint = default_repaint;
	w->fnct.key_hook = default_key_hook;
	w->fnct.expose = default_expose_hook;
	w->wdim = (t_vec2i){{DEFAULT_RESOLUTION}};
	w->ratio = (t_real)w->wdim.d.width / (t_real)w->wdim.d.height;
	if (!(w->mlx = mlx_init()))
		return (1);
	ft_putstr("Librairy Initialised\n");
	if (!(w->win = mlx_new_window(w->mlx,
		w->wdim.d.width, w->wdim.d.height, "Fil De Fer")))
		return (2);
	ft_putstr("Window Created\n");
	if (!(w->img = mlx_new_image(w->mlx, w->wdim.d.width, w->wdim.d.height)))
		return (3);
	ft_putstr("Image Allocated\n");
	if (!(w->pixel = mlx_get_data_addr(w->img,
		&(w->bits_per_pixel), &(w->line_size), &(w->endian))))
		return (4);
	ft_putstr("Image informations Obtained\n");
	mlx_expose_hook(w->win, w->fnct.expose, (void *)w);
	mlx_hook(w->win, 2, 0, w->fnct.key_hook, (void *)w);
	mlx_do_key_autorepeaton(w->mlx);
	if (!(w->g.world = obj_alloc("World")))
		return (5);
	return (!(w->g.cam = camera_alloc()));
}

int				ggl_main(int ac, char **av)
{
	t_env	w;

	if (init_env(&w))
		ft_putstr_fd("Error : Initialisation failed\n", 2);
	else
	{
		ft_putstr("Initialisation Successful\n");
		if (--ac)
		{
			read_av(w.g.world, ac, ++av);
//			w.fnct.repaint = render;
		}
		w.fnct.repaint(&w);
		ft_putnbr(mlx_loop(w.mlx));
		ft_putstr(" <- mlx_loop\n");
		ft_putstr("Loop killed\n");
		destroy_env(&w);
	}
	return (0);
}
