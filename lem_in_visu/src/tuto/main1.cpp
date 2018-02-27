/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 14:45:37 by emarin            #+#    #+#             */
/*   Updated: 2018/02/07 17:13:29 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in_visu.h"

int	main(void)
{
	SDL_Window		*window;
	SDL_Surface		*screen_surface;

	if (SDL_Init(SDL_INIT_VIDEO) != 0 )
		printf("Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
	else
	{
	    if (!(window = SDL_CreateWindow("lem_in visu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)))
		{
			printf("Erreur de création de la fenêtre (%s)\n", SDL_GetError());
			return -1;
		}
		else
		{
			screen_surface = SDL_GetWindowSurface(window);
			SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));
			SDL_UpdateWindowSurface(window);
			SDL_Delay(5000);
		}
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
	return (0);
}
