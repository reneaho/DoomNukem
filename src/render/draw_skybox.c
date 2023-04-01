/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_skybox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfum <kfum@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:09:32 by raho              #+#    #+#             */
/*   Updated: 2023/03/28 09:38:39 by kfum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"
#include "render.h"

void	draw_skybox_image(t_world *world)
{
	static t_img	*skybox = NULL;
	t_point			skypos1;
	t_point			skypos2;
	t_vector2		rot;
	double			x;
	double			y;

	if (world->sdl->render.occlusion.screen_full)
		return ;
	x = world->player->transform.rotation.x;
	y = world->player->transform.rotation.y;
	rot.x = ft_absf(fmodf(x / (2 * PI), 1.0f));
	rot.y = fmodf(y / PI, 1.0f);
	if (skybox == NULL)
		skybox = get_image_by_name(*world->sdl, SKYBOX);
	skypos1 = point_add(point_zero(), (t_point){rot.x * skybox->size.x, (rot.y * skybox->size.y) - 100});
	skypos2 = point_add(point_zero(), (t_point){(rot.x * skybox->size.x) - skybox->size.x, (rot.y * skybox->size.y) - 100});
	draw_image(*world->sdl, skypos1, *skybox, skybox->size);
	draw_image(*world->sdl, skypos2, *skybox, skybox->size);
}
