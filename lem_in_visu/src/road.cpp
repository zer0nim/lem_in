/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   road.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:12:29 by emarin            #+#    #+#             */
/*   Updated: 2018/02/20 14:43:32 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/road.h"

Road::Road(SDL_Renderer **renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 width, Uint32 color)
{
	m_renderer = renderer;
	m_x1 = x1;
	m_y1 = y1;
	m_x2 = x2;
	m_y2 = y2;
	m_width = width;
	m_color = color;
}

void Road::render(Camera *camera)
{
	float	ratio = camera->getStartW() / camera->getCam()->w;
	int	new_m_width = m_width * ratio;

	int tmp_w = (camera->getStartW() - camera->getCam()->w) / 2;
	int tmp_h = (camera->getStartH() - camera->getCam()->h) / 2;

	int midl_x = (camera->getCam()->w / 2);
	int midl_y = (camera->getCam()->h / 2);

	int	new_m_x1 = m_x1 + (( (float)(m_x1 - camera->getCam()->x) / midl_x) * tmp_w) - camera->getCam()->x;
	int	new_m_y1 = m_y1 + (( (float)(m_y1 - camera->getCam()->y) / midl_y) * tmp_h) - camera->getCam()->y;
	int	new_m_x2 = m_x2 + (( (float)(m_x2 - camera->getCam()->x) / midl_x) * tmp_w) - camera->getCam()->x;
	int	new_m_y2 = m_y2 + (( (float)(m_y2 - camera->getCam()->y) / midl_y) * tmp_h) - camera->getCam()->y;

	SDL_Rect window_r = {-new_m_width, -new_m_width, SCREEN_WIDTH + new_m_width*2, SCREEN_HEIGHT + new_m_width*2};

	// render only what is inside the screen
	if (SDL_IntersectRectAndLine(&window_r, &new_m_x1, &new_m_y1, &new_m_x2, &new_m_y2))
		thickLineColor(*m_renderer, new_m_x1, new_m_y1, new_m_x2, new_m_y2, (new_m_width > 255) ? 255 : new_m_width, m_color);
	//BUUUUUG thickLine accept only line width to 255

}
