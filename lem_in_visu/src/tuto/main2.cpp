/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 14:45:37 by emarin            #+#    #+#             */
/*   Updated: 2018/02/07 17:45:52 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in_visu.h"


SDL_Window		*window = NULL;
SDL_Surface		*screen_surface = NULL;
SDL_Surface		*hello_world = NULL;

bool init()
{
	bool success = true;

	//Initialize SDL
	if( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		printf("Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("lem_in visu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if( window == NULL )
		{
			printf("Erreur de création de la fenêtre (%s)\n", SDL_GetError());
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
bool loadMedia()
{
	//Loading success flag
    bool success = true;

    //Load splash image
    hello_world = SDL_LoadBMP("data/hello_world.bmp");
    if (hello_world == NULL)
    {
        printf("Impossible de charger l'image %s! SDL Error: %s\n", "data/hello_world.bmp", SDL_GetError());
        success = false;
    }
    return success;
}
void close()
{
	//Deallocate surface
    SDL_FreeSurface(hello_world);
    hello_world = NULL;
    //Destroy window
    SDL_DestroyWindow(window);
    window = NULL;
    //Quit SDL subsystems
    SDL_Quit();
}

int	main(void)
{
	//Start up SDL and create window
	if (!init())
		printf( "Failed to initialize!\n" );
	else
	{
		//Load media
		if( !loadMedia() )
			printf( "Failed to load media!\n" );
		else
		{
			//Apply the image
			SDL_BlitSurface(hello_world, NULL, screen_surface, NULL);
			//Update the surface
			SDL_UpdateWindowSurface(window);
			//Wait two seconds
            SDL_Delay(2000);
		}
	}
	//Free resources and close SDL
	close();
	return 0;
}
