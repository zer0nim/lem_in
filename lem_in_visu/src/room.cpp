/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:12:29 by emarin            #+#    #+#             */
/*   Updated: 2018/02/16 14:03:35 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/room.h"

Room::Room(LTexture *title, LTexture *room_texture)
{
    m_pos_x = 0;
    m_pos_y = 0;
	m_room_texture = room_texture;
	m_title = title;
}

void Room::render(Camera *camera)
{
	int tmp_w = (camera->getStartW() - camera->getCam()->w) / 2;
	int tmp_h = (camera->getStartH() - camera->getCam()->h) / 2;

	int midl_x = (camera->getCam()->w / 2);
	int midl_y = (camera->getCam()->h / 2);

	int	new_x = m_pos_x + (( (float)(m_pos_x - camera->getCam()->x) / midl_x) * tmp_w);
	int	new_y = m_pos_y + (( (float)(m_pos_y - camera->getCam()->y) / midl_y) * tmp_h);

	float	ratio = camera->getStartW() / camera->getCam()->w;

	int	room_w = m_room_texture->getWidth() * ratio;
	int	room_h = m_room_texture->getHeight() * ratio;

	SDL_Rect renderQuad = {new_x - camera->getCam()->x
						, new_y - camera->getCam()->y
						, room_w, room_h};

	// render only what is inside the screen
	if ((renderQuad.x + room_w > 0 && renderQuad.x - room_w < SCREEN_WIDTH)
		|| (renderQuad.y + room_h > 0 && renderQuad.y - room_h < SCREEN_HEIGHT))
	{
		m_room_texture->render(&renderQuad);
		m_title->render(renderQuad.x, renderQuad.y + room_h);
	}
}

void Room::setPos(int x, int y)
{
	m_pos_x = x;
	m_pos_y = y;
}

int Room::getX()
{
	return (m_pos_x);
}
int Room::getY()
{
	return (m_pos_y);
}

LTexture	*Room::getTitle()
{
	return (m_title);
}
