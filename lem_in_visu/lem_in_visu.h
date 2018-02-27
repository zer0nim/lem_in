/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_visu.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 14:46:38 by emarin            #+#    #+#             */
/*   Updated: 2018/02/19 16:18:46 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEM_IN_VISU_H
# define FT_LEM_IN_VISU_H

# define START_WIDTH 1920
# define START_HEIGHT 1080

# define ROOM_SIZE 180
# define UNIT_SIZE 140

# include <stdio.h>
# include <string>
# include <sstream>
# include <vector>
# include <cmath>
# include <iostream>
# include "include/SDL2/SDL.h"
# include "include/SDL2/SDL_image.h"
# include "include/SDL2/SDL_ttf.h"
# include "include/SDL2/SDL2_gfxPrimitives.h"

extern "C" {
# include "../lem_in.h"
}

bool	init();
bool	loadMedia();
void	close();
void	start_lem_in_visu(t_anthill *anthill);

#endif
