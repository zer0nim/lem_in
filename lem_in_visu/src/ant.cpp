/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:12:29 by emarin            #+#    #+#             */
/*   Updated: 2018/02/20 15:20:59 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ant.h"

Ant::Ant(LTexture *ant_sprite, int pos_x, int pos_y, int ant_nb_frame, SDL_Rect *ant_sprite_clip)
{
    m_pos_x = pos_x;
    m_pos_y = pos_y;
	m_dest_x = pos_x;
	m_dest_y = pos_y;
	m_ant_sprite = ant_sprite;
	m_ant_sprite_clip = ant_sprite_clip;
	m_ant_nb_frame = ant_nb_frame;
	frame = 0;
	animate = false;
	angle = 0.0;
}

void Ant::render(Camera *camera)
{
	//Render current frame
	SDL_Rect* currentClip = &m_ant_sprite_clip[frame / M_REDUCE_RATE];

	int tmp_w = (camera->getStartW() - camera->getCam()->w) / 2;
	int tmp_h = (camera->getStartH() - camera->getCam()->h) / 2;

	int midl_x = (camera->getCam()->w / 2);
	int midl_y = (camera->getCam()->h / 2);

	int	new_x = m_pos_x + (( (float)(m_pos_x - camera->getCam()->x) / midl_x) * tmp_w);
	int	new_y = m_pos_y + (( (float)(m_pos_y - camera->getCam()->y) / midl_y) * tmp_h);

	float	ratio = camera->getStartW() / camera->getCam()->w;

	int	clip_w = currentClip->w * ratio * 0.8;
	int	clip_h = currentClip->h * ratio * 0.8;

	SDL_Rect renderQuad = {(new_x - (clip_w / 2)) - camera->getCam()->x
						, (new_y - (clip_h / 2)) - camera->getCam()->y
						, clip_w, clip_h};

	m_ant_sprite->render(&renderQuad, currentClip, angle);

	if (animate)
		++frame;
	//Cycle animation
	if (frame / M_REDUCE_RATE >= m_ant_nb_frame)
		frame = 0;
}

void Ant::moveTo(int p2_x, int p2_y)
{
	if (NEXT_STEP)
	{
		m_pos_x = p2_x;
		m_pos_y = p2_y;
		animate = false;
		PAUSE = true;
	}
	else if (PAUSE)
		animate = false;
	else
	{
		animate = true;

		// angle in radian
		double	rangle = std::atan2(p2_y - m_pos_y, p2_x - m_pos_x);
		angle = 180 + rangle / M_PI * 180;
		m_pos_x += ANT_VEL * std::cos(rangle);
		m_pos_y += ANT_VEL * std::sin(rangle);

		if ((m_pos_x <= p2_x + ANT_VEL && m_pos_x >= p2_x - ANT_VEL) && (m_pos_y <= p2_y + ANT_VEL && m_pos_y >= p2_y - ANT_VEL))
		{
			m_pos_x = p2_x;
			m_pos_y = p2_y;
			animate = false;
		}
	}
}

void Ant::setPos(int x, int y)
{
	m_pos_x = x;
	m_pos_y = y;
}

void Ant::setDest(int x, int y)
{
 	m_dest_x = x;
	m_dest_y = y;
}

int	Ant::getDestX()
{
	return (m_dest_x);
}

int	Ant::getDestY()
{
	return (m_dest_y);
}

int	Ant::getX()
{
	return (m_pos_x);
}

int	Ant::getY()
{
	return (m_pos_y);
}
