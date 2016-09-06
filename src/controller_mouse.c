/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_mouse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 22:31:25 by angagnie          #+#    #+#             */
/*   Updated: 2016/09/06 06:41:24 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keys.h"
#include "ggl.h"

int				default_mouse_hook(int button, int x, int y, void *param)
{
	t_env *const	w = param;

	(void)x;
	(void)y;
	ft_putstr("Mouse click : ");
	ft_putnbr(button);
	ft_putstr("\n");
	w->fnct.repaint(w);
	w->fnct.expose(w);
	return (0);
}

int				default_mouse_move_hook(int x, int y, void *param)
{
	t_env *const	w = param;

	(void)x;
	(void)y;
	(void)w;
	return (0);
}
