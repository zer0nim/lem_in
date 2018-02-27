/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main4.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 14:45:37 by emarin            #+#    #+#             */
/*   Updated: 2018/02/08 11:10:33 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in_visu.h"

//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

SDL_Window		*window = NULL;
SDL_Surface		*screen_surface = NULL;
//The images that correspond to a keypress
SDL_Surface* key_press_surfaces[KEY_PRESS_SURFACE_TOTAL];
//Current displayed image
SDL_Surface* current_surface = NULL;




SDL_Surface* loadSurface(std::string path)
{
    //Load image at specified path
    SDL_Surface* loaded_surface = SDL_LoadBMP(path.c_str());
    if (loaded_surface == NULL)
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    return loaded_surface;
}

bool init()
{
	bool success = true;

	//Initialize SDL
	if( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("lem_in visu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if( window == NULL )
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}
	return success;
}
//data/hello_world.bmp
bool loadMedia()
{
	//Loading success flag
    bool success = true;

    //Load default surface
    key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("data/press.bmp");
    if( key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL )
    {
        printf("Failed to load default image!\n");
        success = false;
    }
    //Load up surface
    key_press_surfaces[KEY_PRESS_SURFACE_UP] = loadSurface("data/up.bmp");
    if( key_press_surfaces[KEY_PRESS_SURFACE_UP] == NULL )
    {
        printf("Failed to load up image!\n");
        success = false;
    }
    //Load down surface
    key_press_surfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("data/down.bmp");
    if( key_press_surfaces[KEY_PRESS_SURFACE_DOWN] == NULL )
    {
        printf("Failed to load down image!\n");
        success = false;
    }
    //Load left surface
    key_press_surfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("data/left.bmp");
    if( key_press_surfaces[KEY_PRESS_SURFACE_LEFT] == NULL )
    {
        printf("Failed to load left image!\n");
        success = false;
    }
    //Load right surface
    key_press_surfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("data/right.bmp");
    if( key_press_surfaces[KEY_PRESS_SURFACE_RIGHT] == NULL )
    {
        printf("Failed to load right image!\n");
        success = false;
    }

    return success;
}

void close()
{
	//Deallocate surfaces
	for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
	{
		SDL_FreeSurface(key_press_surfaces[ i ]);
		key_press_surfaces[i] = NULL;
	}

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int	main(void)
{
	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;

	//Start up SDL and create window
	if (!init())
		printf( "Failed to initialize!\n" );
	else
	{
		//Load media
		if (!loadMedia())
			printf( "Failed to load media!\n" );
		else
		{
			//Set default current surface
            current_surface = key_press_surfaces[ KEY_PRESS_SURFACE_DEFAULT ];
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
						quit = true;
					else if( e.type == SDL_KEYDOWN )
					{
						//Select surfaces based on key press
						switch( e.key.keysym.sym )
						{
							case SDLK_UP:
							current_surface = key_press_surfaces[ KEY_PRESS_SURFACE_UP ];
							break;

							case SDLK_DOWN:
							current_surface = key_press_surfaces[ KEY_PRESS_SURFACE_DOWN ];
							break;

							case SDLK_LEFT:
							current_surface = key_press_surfaces[ KEY_PRESS_SURFACE_LEFT ];
							break;

							case SDLK_RIGHT:
							current_surface = key_press_surfaces[ KEY_PRESS_SURFACE_RIGHT ];
							break;

							default:
							current_surface = key_press_surfaces[ KEY_PRESS_SURFACE_DEFAULT ];
							break;
						}
					}
				}
				SDL_BlitSurface(current_surface, NULL, screen_surface, NULL);
				SDL_UpdateWindowSurface(window);
			}
		}
	}
	//Free resources and close SDL
	close();
	return 0;
}
