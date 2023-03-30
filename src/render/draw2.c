/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 22:03:23 by raho              #+#    #+#             */
/*   Updated: 2023/03/27 11:58:08 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"
#include "render.h"
#include "vectors.h"
#include "player.h"

void	draw_crosshair(t_world *world)
{
	//drawcircle(*sdl, point_div(sdl->screensize, 2), 4, CLR_BLUE);
	t_crosshair	*ch;

	ch = &world->player->crosshair;
	drawline(*world->sdl, ch->horizontal_start, ch->horizontal_end, CLR_WHITE_WARM);
	drawline(*world->sdl, ch->vertical_start, ch->vertical_end, CLR_WHITE_WARM);
}

t_rectangle	empty_rect(void)
{
	return ((t_rectangle){0});
}
