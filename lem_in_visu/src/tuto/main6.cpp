/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:02:26 by emarin            #+#    #+#             */
/*   Updated: 2018/02/08 11:11:04 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in_visu.h"

//Key press surfaces constants
enum KeyPressSurfaces
{
    SURFACE_DEFAULT,
    SURFACE_TOTAL
};

SDL_Window		*window = NULL;
SDL_Surface		*screen_surface = NULL;
//The images that correspond to a keypress
SDL_Surface* key_press_surfaces[SURFACE_TOTAL];
//Current displayed image
SDL_Surface* current_surface = NULL;



SDL_Surface* loadSurface(std::string path)
{
    //The final optimized image
    SDL_Surface* optimized_surface = NULL;

    //Load image at specified path
    SDL_Surface* loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface == NULL)
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    else
    {
        //Convert surface to screen format
        optimized_surface = SDL_ConvertSurface(loaded_surface, screen_surface->format, 0);
        if (optimized_surface == NULL)
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());

        //Get rid of old loaded surface
        SDL_FreeSurface(loaded_surface);
    }
    return optimized_surface;
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
			//Initialize PNG loading
            int img_flags = IMG_INIT_PNG;
            if (!(IMG_Init(img_flags) & img_flags))
            {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            }
            else
            {
                //Get window surface
                screen_surface = SDL_GetWindowSurface(window);
            }
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
    key_press_surfaces[SURFACE_DEFAULT] = loadSurface("data/dice.png");
    if (key_press_surfaces[SURFACE_DEFAULT] == NULL)
    {
        printf("Failed to load default image!\n");
        success = false;
    }

    return success;
}

void close()
{
	//Deallocate surfaces
	for (int i = 0; i < SURFACE_TOTAL; ++i)
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
            current_surface = key_press_surfaces[SURFACE_DEFAULT];
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
						quit = true;
				}
				//Apply the image stretched
				SDL_Rect stretchRect;
				stretchRect.w = 640;
				stretchRect.h = 480;
				stretchRect.x = SCREEN_WIDTH / 2 - stretchRect.w / 2;
				stretchRect.y = SCREEN_HEIGHT / 2 - stretchRect.h / 2;
				SDL_BlitScaled(current_surface, NULL, screen_surface, &stretchRect);
				SDL_UpdateWindowSurface(window);
			}
		}
	}
	//Free resources and close SDL
	close();
	return 0;
}
