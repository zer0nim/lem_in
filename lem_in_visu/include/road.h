/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   road.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:12:43 by emarin            #+#    #+#             */
/*   Updated: 2018/02/15 11:47:27 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROAD_H
# define ROAD_H

# include "../lem_in_visu.h"
# include "camera.h"

class Road
{
    public:

		Road(SDL_Renderer **renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 width, Uint32 color);

		void render(Camera *camera);

    private:
		SDL_Renderer **m_renderer;
		Sint16 m_x1;
		Sint16 m_y1;
		Sint16 m_x2;
		Sint16 m_y2;
		Uint8 m_width;
		Uint32 m_color;
};

#endif
