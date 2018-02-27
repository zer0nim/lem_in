/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:12:43 by emarin            #+#    #+#             */
/*   Updated: 2018/02/20 14:59:25 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "../lem_in_visu.h"

extern int SCREEN_WIDTH, SCREEN_HEIGHT;

class Camera
{
    public:
		Camera(int x = 0, int y = 0, int width = SCREEN_WIDTH, int height = SCREEN_HEIGHT, int limitX = -1, int limitY = -1);

		// reset camera to default value
		void 		reset();

		// Velocity
		static const int CAM_VEL = 10;

		// Control the camera movement
		void		handleEvent(SDL_Event &e);

		// Moves the dot
		void		move();

		SDL_Rect	*getCam();

		int			getCurrentX();
		int			getCurrentY();

		float		getStartW();
		float		getStartH();
		float		getLastW();
		float		getLastH();

		void		setLimitX(int limitX);
		void		setLimitY(int limitY);

    private:
		SDL_Rect m_camera;

		float mVelX, mVelY, mVelZoom, m_start_w, m_start_h, last_w, last_h;

		int	m_limitX, m_limitY, current_x, current_y;
};

#endif
