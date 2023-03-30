#include "doomnukem.h"
#include "editor_tools.h"

void	quit_editor(void)
{
	SDL_Quit();
	exit (0);
}

void	quit_playmode(void)
{
	SDL_Quit();
	exit(0);
}

void	quit_game(void)
{
	SDL_Quit();
	exit(0);
}

void	quit_save_editor(t_editor *ed)
{
	world_save_to_file(ed->world);
	SDL_Quit();
	exit (0);
}
