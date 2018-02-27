/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:12:29 by emarin            #+#    #+#             */
/*   Updated: 2018/02/20 14:53:01 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/camera.h"

Camera::Camera(int x, int y, int width, int height, int limitX, int limitY)
{
	m_camera.x = x;
	m_camera.y = y;
	m_camera.w = width;
	m_camera.h = height;
	last_w =  m_camera.w;
	last_h =  m_camera.h;
	m_limitX = limitX;
	m_limitY = limitY;
	m_start_w = width;
	m_start_h = height;
    mVelX = 0;
    mVelY = 0;
	mVelZoom = 0;

	current_x = 0;
	current_y = 0;
}

void		Camera::reset()
{
	m_camera.x = 0;
	m_camera.y = 0;
	m_camera.w = SCREEN_WIDTH;
	m_camera.h = SCREEN_HEIGHT;
	last_w =  m_camera.w;
	last_h =  m_camera.h;
	m_start_w = SCREEN_WIDTH;
	m_start_h = SCREEN_HEIGHT;
	mVelX = 0;
	mVelY = 0;
	mVelZoom = 0;
	current_x = 0;
	current_y = 0;
}

void		Camera::handleEvent(SDL_Event &e)
{
	float speed = CAM_VEL * (float)(m_camera.w / m_start_w);

	if (speed < 1)
		speed = 1;
    // Key pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
		if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w)
			mVelY = -speed;
		else if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s)
			mVelY = speed;
		else if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a)
			mVelX = -speed;
		else if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d)
			mVelX = speed;
		else if (e.key.keysym.sym == SDLK_LSHIFT || e.key.keysym.sym == SDLK_RSHIFT)
			mVelZoom = -CAM_VEL;
		else if (e.key.keysym.sym == SDLK_LCTRL || e.key.keysym.sym == SDLK_RCTRL)
			mVelZoom = CAM_VEL;
    }
    // Key released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
		if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w)
			mVelY = 0;
		else if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s)
			mVelY = 0;
		else if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a)
			mVelX = 0;
		else if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d)
			mVelX = 0;
		else if (e.key.keysym.sym == SDLK_LSHIFT || e.key.keysym.sym == SDLK_RSHIFT)
			mVelZoom = 0;
		else if (e.key.keysym.sym == SDLK_LCTRL || e.key.keysym.sym == SDLK_RCTRL)
			mVelZoom = 0;
    }
}

SDL_Rect	*Camera::getCam()
{
	return (&m_camera);
}

void		Camera::setLimitX(int limitX)
{
	m_limitX = limitX;
}
void		Camera::setLimitY(int limitY)
{
	m_limitY = limitY;
}

int			Camera::getCurrentX()
{
	return (current_x);
}

int			Camera::getCurrentY()
{
	return (current_y);
}

float		Camera::getStartW()
{
	return (m_start_w);
}

float		Camera::getStartH()
{
	return (m_start_h);
}

float		Camera::getLastW()
{
	return (last_w);
}
float		Camera::getLastH()
{
	return (last_h);
}

void		Camera::move()
{
	// float ratio = (float)(m_camera.w / m_start_w);

	// zoom in our out
	float	new_h = (m_camera.h * (float)(m_camera.w + (mVelZoom * 2)) / m_camera.w);

	if (new_h > 200)
	{
		if (mVelZoom != 0 && (mVelZoom < 0 || !((m_camera.y + m_camera.h >= m_limitY) || (m_camera.x + m_camera.w >= m_limitX))))
		{
			last_w =  m_camera.w;
			last_h =  m_camera.h;

			m_camera.w += mVelZoom * 2;
			m_camera.h = new_h;

			m_camera.x -= mVelZoom;
			m_camera.y += (last_h - new_h) / 2;
		}
	}

	// Move the camera horizontally
    m_camera.x += mVelX;
	current_x += mVelX;
    // Block the camera to the border of the map
    if (m_limitX != -1 && m_camera.x <= 0)
	{
		m_camera.x = 0;
		current_x = 0;
	}
	else if (m_camera.x + m_camera.w > m_limitX)
	{
        m_camera.x = m_limitX - m_camera.w;
		current_x = m_limitX - m_camera.w;
	}

    //Move the camera vertically
    m_camera.y += mVelY;
	current_y += mVelY;
    // Block the camera to the border of the map
    if (m_limitY != -1 && m_camera.y <= 0)
	{
		m_camera.y = 0;
		current_y = 0;
	}
	else if (m_camera.y + m_camera.h > m_limitY)
	{
        m_camera.y = m_limitY - m_camera.h;
		current_y = m_limitY - m_camera.h;
	}
}
