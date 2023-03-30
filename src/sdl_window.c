/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 14:59:55 by raho              #+#    #+#             */
/*   Updated: 2023/03/27 12:23:26 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"
#include "render.h"

void	sdl_windowevents(SDL_Event e, t_sdlcontext *sdl)
{
	doomlog(LOG_NORMAL, s_itoa(e.window.event));
	if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		sdl->window_exists = !sdl->window_exists;
		if (sdl->window_exists == true)
		{
			sdl->window_surface = SDL_GetWindowSurface(sdl->window);
			if (sdl->window_surface == NULL)
				doomlog(LOG_EC_SDL_GETWINDOW_SURFACE, NULL);
		}
		else
			SDL_FreeSurface(sdl->window_surface);
	}
}

void	create_sdl_window(t_sdlcontext *sdl)
{
	SDL_DisplayMode	dmode;
	SDL_Event		e;

	if (SDL_GetCurrentDisplayMode(0, &dmode) < 0)
		doomlog(LOG_EC_SDL_GETCURRENTDISPLAYMODE, NULL);
	sdl->window_w = dmode.w;
	sdl->window_h = dmode.h;
	sdl->screensize = (t_point){sdl->window_w, sdl->window_h};
	sdl->window = SDL_CreateWindow("DoomNukem", 0, 0, \
		sdl->window_w, sdl->window_h, SDL_WINDOW_FULLSCREEN);
	if (sdl->window == NULL)
		doomlog(LOG_EC_SDL_CREATEWINDOW, NULL);
	if (SDL_SetWindowFullscreen(sdl->window, SDL_WINDOW_FULLSCREEN) < 0)
		doomlog(LOG_EC_SDL_SETWINDOWFULLSCREEN, NULL);
	while (SDL_PollEvent(&e))
		sdl_windowevents(e, sdl);
}

void	free_sdl_stuff(t_sdlcontext *sdl)
{
	if (sdl->zbuffer != NULL)
		free(sdl->zbuffer);
	if (sdl->surface != NULL)
		SDL_FreeSurface(sdl->surface);
	if (sdl->window_surface != NULL)
		SDL_FreeSurface(sdl->window_surface);
	if (sdl->window != NULL)
		SDL_DestroyWindow(sdl->window);
	free_render(sdl->render);
	if (sdl->bitmask.tile != NULL)
		free(sdl->bitmask.tile);
	if (sdl->scaling_buffer != NULL)
		free(sdl->scaling_buffer);
}

//TODO: free bitmask.tile
void	alloc_occlusion(t_sdlcontext *sdl)
{
	sdl->bitmask.tile = prot_memalloc(sizeof(t_tile) * \
			((sdl->window_h * sdl->window_w) / 64));
	sdl->bitmask.bitmask_chunks.x = sdl->window_w / 16;
	sdl->bitmask.bitmask_chunks.y = sdl->window_h / 8;
	sdl->bitmask.tile_chunks.x = sdl->window_w / 8;
	sdl->bitmask.tile_chunks.y = sdl->window_h / 8;
}

void	set_sdl_settings(t_sdlcontext *sdl)
{
	t_graphic_prefs	prefs;

	free_sdl_stuff(sdl);
	sdl->resolution_scaling = ft_clampf(DEFAULT_RES_SCALING, 0.25f, 1.0f);
	sdl->audio.sfx_volume = 5.0f;
	create_sdl_window(sdl);
	sdl->surface = SDL_CreateRGBSurfaceWithFormat(SDL_SWSURFACE, \
				sdl->window_w, sdl->window_h, 32, SDL_PIXELFORMAT_ARGB8888);
	if (sdl->surface == NULL)
		doomlog(LOG_EC_SDL_CREATERGBSURFACE, NULL);
	sdl->zbuffer = prot_memalloc(sdl->window_w * sdl->window_h * sizeof(float));
	sdl->scaling_buffer = prot_memalloc(sdl->window_w * sdl->window_w * \
											sizeof(uint32_t));
	alloc_occlusion(sdl);
	sdl->render = init_render(*sdl);
}

void	create_sdlcontext(t_app_argument app_argument, t_sdlcontext	*sdl)
{
	ft_bzero(sdl, sizeof(t_sdlcontext));
	if (SDL_Init(SDL_INIT_VIDEO) < 0 \
		|| SDL_Init(SDL_INIT_EVENTS) < 0 \
		|| SDL_Init(SDL_INIT_GAMECONTROLLER) < 0 \
		|| TTF_Init() < 0)
		doomlog(LOG_EC_SDL_INIT, NULL);
	set_sdl_settings(sdl);
	if (app_argument.app_mode == APPMODE_EDIT)
		editor_load_assets(sdl);
	else if (app_argument.app_mode == APPMODE_PLAY)
		playmode_load_assets(app_argument.level_name, sdl);
}

	// 0 SDL_WINDOWEVENT_NONE,           /**< Never used */
    // 1 SDL_WINDOWEVENT_SHOWN,          /**< Window has been shown */
    // 2 SDL_WINDOWEVENT_HIDDEN,         /**< Window has been hidden */
    // 3 SDL_WINDOWEVENT_EXPOSED,        /**< Window has been exposed and should be
    //                                      redrawn */
    // 4 SDL_WINDOWEVENT_MOVED,          /**< Window has been moved to data1, data2
    //                                  */
    // 5 SDL_WINDOWEVENT_RESIZED,        /**< Window has been resized to data1xdata2 */
    // 6 SDL_WINDOWEVENT_SIZE_CHANGED,   /**< The window size has changed, either as
    //                                      a result of an API call or through the
    //                                      system or user changing the window size. */
    // 7 SDL_WINDOWEVENT_MINIMIZED,      /**< Window has been minimized */
    // 8 SDL_WINDOWEVENT_MAXIMIZED,      /**< Window has been maximized */
    // 9 SDL_WINDOWEVENT_RESTORED,       /**< Window has been restored to normal size
    //                                      and position */
    // 10 SDL_WINDOWEVENT_ENTER,          /**< Window has gained mouse focus */
    // 11 SDL_WINDOWEVENT_LEAVE,          /**< Window has lost mouse focus */
    // 12 SDL_WINDOWEVENT_FOCUS_GAINED,   /**< Window has gained keyboard focus */
    // 13 SDL_WINDOWEVENT_FOCUS_LOST,     /**< Window has lost keyboard focus */
    // 14 SDL_WINDOWEVENT_CLOSE,          /**< The window manager requests that the window be closed */
    // 15 SDL_WINDOWEVENT_TAKE_FOCUS,     /**< Window is being offered a focus (should SetWindowInputFocus() on itself or a subwindow, or ignore) */
    // 16 SDL_WINDOWEVENT_HIT_TEST