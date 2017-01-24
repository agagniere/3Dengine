/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/30 19:15:59 by angagnie          #+#    #+#             */
/*   Updated: 2017/01/24 18:11:09 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
** Wolf Main
*/

int		the_main(int ac, char **av)
{
	t_wlf			w[1];
	t_env *const	e = (t_env *)w;

	(void)ac;
	(void)av;
	env_new(e);
	e->fnct.repaint = &wolf_repaint;
	ggl_main(e);
	w->fov = DEFAULT_FOV;
	return (0);
}
