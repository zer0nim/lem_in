/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_visu.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 20:21:58 by emarin            #+#    #+#             */
/*   Updated: 2018/02/21 10:38:18 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in_visu.h"
# include "../include/ltexture.h"
# include "../include/camera.h"
# include "../include/room.h"
# include "../include/road.h"
# include "../include/ant.h"
# include "../include/lem_in_visu.h"

# include "../include/lwindow.h"

int		SCREEN_WIDTH = START_WIDTH;
int		SCREEN_HEIGHT = START_HEIGHT;
bool	PAUSE = true;
bool	NEXT_STEP = false;
int		STEP = 0;

bool init(LWindow *window, SDL_Renderer **renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			printf("Warning: Linear texture filtering not enabled!");

		if (TTF_Init() == -1)
		{
			printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
			return false;
		}
		else
		{
			if (!window->init(std::string("lem_in visu")))
			{
				printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
				return false;
			}
			else
			{
				*renderer = window->createRenderer();
				if (*renderer == NULL)
				{
					printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
					return false;
				}
				else
				{
					SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0xFF);
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool loadMedia(LTexture *room_texture, LTexture *room_start_texture, LTexture *room_end_texture, int ant_nb_frame, SDL_Rect *ant_sprite_clip, LTexture *ant_sprite, TTF_Font **font)
{
	// Load room texture
	if (!room_texture->loadFromFile("data/room.png"))
	{
		printf("Failed to load room texture!\n");
		return false;
	}
	if (!room_start_texture->loadFromFile("data/start.png"))
	{
		printf("Failed to load start texture!\n");
		return false;
	}
	if (!room_end_texture->loadFromFile("data/end.png"))
	{
		printf("Failed to load end texture!\n");
		return false;
	}
	room_texture->setSize(ROOM_SIZE, ROOM_SIZE);
	room_start_texture->setSize(ROOM_SIZE, ROOM_SIZE);
	room_end_texture->setSize(ROOM_SIZE, ROOM_SIZE);

	// Load ant sprite sheet texture
	if (!ant_sprite->loadFromFile("data/ant.bmp"))
	{
		printf("Failed to load ant texture!\n");
		return false;
	}
	for (int i = 0; i < ant_nb_frame; ++i) {
		// Set top left sprite
		ant_sprite_clip[i].x = i * (ant_sprite->getWidth() / ant_nb_frame);
		ant_sprite_clip[i].y =  0;
		ant_sprite_clip[i].w = 64;
		ant_sprite_clip[i].h = 56;
	}

	// load font
	*font = TTF_OpenFont("data/Raleway-Regular.ttf", 22);
	if (*font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		return (false);
	}
	return true;
}

void close(LWindow *window, SDL_Renderer **renderer, LTexture *room_texture, LTexture *room_start_texture, LTexture *room_end_texture, LTexture *ant_sprite, std::vector<Room> *rooms, TTF_Font **font, LTexture *text_texture)
{
	for (std::vector<Room>::iterator room = rooms->begin(); room != rooms->end(); ++room) {
		room->getTitle()->free();
	}
	TTF_CloseFont(*font);
	room_texture->free();
	room_start_texture->free();
	room_end_texture->free();
	ant_sprite->free();
	text_texture->free();
	SDL_DestroyRenderer(*renderer);
	window->free();
	*renderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

std::vector<Road>	initRoad(SDL_Renderer **renderer, t_anthill *anthill)
{
	std::vector<Road>	roads;
	char				already_printed;
	int					i;
	int					pos;
	t_room				*tmp;
	int					fickness = ROOM_SIZE * 0.4;

	pos = 0;
	tmp = anthill->room;
	while (tmp)
	{
		if (tmp->near)
		{
			i = -1;
			while ((tmp->near)[++i])
			{
				already_printed = ft_check_alrdy_print(tmp, (tmp->near)[i], anthill->room, pos);
				if (!already_printed)
				{
					roads.push_back(Road(renderer
						,tmp->x * UNIT_SIZE + (ROOM_SIZE / 2)
						, tmp->y * UNIT_SIZE + (ROOM_SIZE / 2)
						, ((tmp->near)[i])->x * UNIT_SIZE + (ROOM_SIZE / 2)
						, ((tmp->near)[i])->y * UNIT_SIZE + (ROOM_SIZE / 2)
						, fickness
						, 0xFF86ABD1));
				}
			}
		}
		tmp = tmp->next;
		++pos;
	}
	return (roads);
}

std::vector<Room>	initRoom(SDL_Renderer **renderer, LTexture *room_texture, LTexture *room_start_texture
	, LTexture *room_end_texture, t_anthill *anthill, Camera *camera, TTF_Font *font, SDL_Color textColor)
{
	t_room				*tmp;
	std::vector<Room>	rooms;
	int					room_len;
	int					max_x = 0, max_y = 0;
	LTexture	*text_title = NULL;

	room_len = ft_nb_room(anthill);
	tmp = anthill->room;
	rooms.reserve(room_len);
	for (int i = 0; i < room_len; ++i)
	{
		text_title = new LTexture(renderer);

		if (!text_title->loadFromRenderedText(font, tmp->name, textColor))
			printf("Failed to render text texture!\n");
		// text_title->setAlpha(100);

		if (anthill->start == tmp)
			rooms.push_back(Room(text_title, room_start_texture));
		else if (anthill->end == tmp)
			rooms.push_back(Room(text_title, room_end_texture));
		else
			rooms.push_back(Room(text_title, room_texture));
		rooms.back().setPos(tmp->x * UNIT_SIZE, tmp->y * UNIT_SIZE);
		if ((tmp->x * UNIT_SIZE + ROOM_SIZE) > max_x)
			max_x = tmp->x * UNIT_SIZE + ROOM_SIZE;
		if ((tmp->y * UNIT_SIZE + ROOM_SIZE) > max_y)
			max_y = tmp->y * UNIT_SIZE + ROOM_SIZE;
		tmp = tmp->next;
	}

	float	ratio_dwn = (float)SCREEN_HEIGHT / SCREEN_WIDTH;
	float	ratio_up = (float)SCREEN_WIDTH / SCREEN_HEIGHT;

	// scale texture to fit screen ratio and allow to see the full map on zoom out
	if (max_x >= max_y)
	{
		if (max_x * ratio_dwn < max_y)
			max_x = max_y * ratio_up;
		else
			max_y = max_x * ratio_dwn;
	}
	else
	{
		if (max_y * ratio_dwn < max_x)
			max_y = max_x * ratio_up;
		else
			max_x = max_y * ratio_dwn;
	}

	camera->setLimitX(max_x);
	camera->setLimitY(max_y);
	return (rooms);
}

void	updateCamLimit(t_anthill *anthill, Camera *camera)
{
	t_room				*tmp;
	int					room_len;
	int					max_x = 0, max_y = 0;

	room_len = ft_nb_room(anthill);
	tmp = anthill->room;
	for (int i = 0; i < room_len; ++i)
	{
		if ((tmp->x * UNIT_SIZE + ROOM_SIZE) > max_x)
			max_x = tmp->x * UNIT_SIZE + ROOM_SIZE;
		if ((tmp->y * UNIT_SIZE + ROOM_SIZE) > max_y)
			max_y = tmp->y * UNIT_SIZE + ROOM_SIZE;
		tmp = tmp->next;
	}

	float	ratio_dwn = (float)SCREEN_HEIGHT / SCREEN_WIDTH;
	float	ratio_up = (float)SCREEN_WIDTH / SCREEN_HEIGHT;

	// scale texture to fit screen ratio and allow to see the full map on zoom out
	if (max_x >= max_y)
	{
		if (max_x * ratio_dwn < max_y)
			max_x = max_y * ratio_up;
		else
			max_y = max_x * ratio_dwn;
	}
	else
	{
		if (max_y * ratio_dwn < max_x)
			max_y = max_x * ratio_up;
		else
			max_x = max_y * ratio_dwn;
	}

	camera->setLimitX(max_x);
	camera->setLimitY(max_y);
}

void			renderMap(std::vector<Road> *roads, std::vector<Room> *rooms, std::vector<Ant> *ants, Camera *camera, t_anthill *anthill)
{
	for (std::vector<Road>::iterator road = roads->begin(); road != roads->end(); ++road) {
		road->render(camera);
	}
	for (std::vector<Room>::iterator room = rooms->begin(); room != rooms->end(); ++room) {
		room->render(camera);
	}
	bool	as_moved = false;
	int		tmp_x, tmp_y;
	for (std::vector<Ant>::iterator ant = ants->begin(); ant != ants->end(); ++ant)
	{
		tmp_x = ant->getX();
		tmp_y = ant->getY();
		ant->moveTo(ant->getDestX(), ant->getDestY());

		// printf("x=%d, y=%d, dest_x=%d, dest_y=%d\n", ant->getX(), ant->getY(), ant->getDestX(), ant->getDestY());
		if (ant->getDestX() != ant->getX() || ant->getDestY() != ant->getY())
			as_moved = true;
		ant->render(camera);
	}
	NEXT_STEP = false;
	if (!as_moved)
		get_next_move(ants, anthill);
}

std::vector<Ant>	initAnt(t_anthill *anthill, LTexture *ant_sprite, int ant_nb_frame, SDL_Rect *ant_sprite_clip)
{
	std::vector<Ant>	ants;
	int	start_x = anthill->start->x * UNIT_SIZE + ROOM_SIZE / 2;
	int	start_y = anthill->start->y * UNIT_SIZE + ROOM_SIZE / 2;

	for (int i = 0; i < anthill->ant_len; ++i)
	{
		ants.push_back(Ant(ant_sprite, start_x, start_y, ant_nb_frame, ant_sprite_clip));
	}
	return (ants);
}

int				nb_ant_at_end(t_anthill *anthill, std::vector<Ant> *ants)
{
	int arrived = 0;

	for (std::vector<Ant>::iterator ant = ants->begin(); ant != ants->end(); ++ant)
	{
		int tmp_x = ant->getX();
		int tmp_y = ant->getY();
		int end_x = anthill->end->x * UNIT_SIZE + ROOM_SIZE / 2;
		int end_y = anthill->end->y * UNIT_SIZE + ROOM_SIZE / 2;
		if (tmp_x == end_x && tmp_y == end_y)
			++arrived;
	}
	return (arrived);
}

void			renderMenu(LWindow *window, SDL_Renderer **renderer, t_anthill *anthill, std::vector<Ant> *ants, TTF_Font *font, LTexture *text_texture)
{
	SDL_Color textColor = {255, 255, 255};
	int y = (SCREEN_HEIGHT - 22 > 0) ? SCREEN_HEIGHT - 22 : 0;
	SDL_Rect back = {2, y, 400, 20};
	int x = 3 + ((float)nb_ant_at_end(anthill, ants) / anthill->ant_len * 398);
	int w = 401 - x;
	SDL_Rect front = {x, y + 1, w, 18};

	SDL_SetRenderDrawColor(*renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderFillRect(*renderer, &back);
	SDL_SetRenderDrawColor(*renderer, 0x0, 0x0, 0x0, 0xff);
	SDL_RenderFillRect(*renderer, &front);


	std::stringstream text_str;
    text_str << "Etape " << STEP << '\n';
	if (!text_texture->loadFromRenderedText(font, (char*)text_str.str().c_str(), textColor))
	    printf( "Unable to render text state texture!\n" );
	text_texture->render(2, y - 28);
}

void			start_lem_in_visu(t_anthill *anthill)
{
	LWindow				window;
	SDL_Renderer		*renderer = NULL;
	LTexture			room_texture(&renderer);
	LTexture			room_start_texture(&renderer);
	LTexture			room_end_texture(&renderer);
	LTexture			text_texture(&renderer);
	std::vector<Road>	roads;
	std::vector<Room>	rooms;
	std::vector<Ant>	ants;
	Camera				camera;
	//ant animation
	int					ant_nb_frame = 4;
	SDL_Rect			ant_sprite_clip[ant_nb_frame];
	LTexture			ant_sprite(&renderer);
	//Globally used font
	TTF_Font			*font = NULL;
	SDL_Color			textColor = {226, 129, 0};

	if (!init(&window, &renderer))
		printf("Failed to initialize!\n");
	else
	{
		if (!loadMedia(&room_texture, &room_start_texture, &room_end_texture, ant_nb_frame, ant_sprite_clip, &ant_sprite, &font))
			printf("Failed to load media!\n");
		else
		{
			bool quit = false;
			SDL_Event e;

			rooms = initRoom(&renderer, &room_texture, &room_start_texture, &room_end_texture, anthill, &camera, font, textColor);
			roads = initRoad(&renderer, anthill);
			ants = initAnt(anthill, &ant_sprite, ant_nb_frame, ant_sprite_clip);


			while (quit == false)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
						quit = true;
					else if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
					{
						if (e.key.keysym.sym == SDLK_SPACE)
							PAUSE = !PAUSE;
						else if (e.key.keysym.sym == SDLK_RALT)
							NEXT_STEP = true;
					}
					camera.handleEvent(e);
					window.handleEvent(e, &renderer);
					//Window event occured
					if (e.type == SDL_WINDOWEVENT
					&& e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
					{
						updateCamLimit(anthill, &camera);
						camera.reset();
					}
				}
				if (!window.isMinimized())
				{
					//Clear screen
					SDL_SetRenderDrawColor(renderer, 0x21, 0x1a, 0x15, 0xff);
					SDL_RenderClear(renderer);

					camera.move();

					renderMap(&roads, &rooms, &ants, &camera, anthill);
					renderMenu(&window, &renderer, anthill, &ants,  font, &text_texture);

					SDL_RenderPresent(renderer);
				}
			}
		}
	}
	close(&window, &renderer, &room_texture, &room_start_texture, &room_end_texture, &ant_sprite, &rooms, &font, &text_texture);
}
