/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:12:43 by emarin            #+#    #+#             */
/*   Updated: 2018/02/20 15:18:45 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANT_H
# define ANT_H

# include "../lem_in_visu.h"
# include "ltexture.h"
# include "camera.h"

extern bool PAUSE;
extern bool	NEXT_STEP;

class Ant
{
    public:
		Ant(LTexture *ant_sprite, int pos_x, int pos_y, int ant_nb_frame, SDL_Rect *ant_sprite_clip);

		static const int ANT_VEL = 4;

		void	render(Camera *camera);

		void	setPos(int x, int y);
		void	setDest(int x, int y);

		int		getX();
		int		getY();
		int		getDestX();
		int		getDestY();

		void	moveTo(int p2_x, int p2_y);

    private:
		float				m_pos_x, m_pos_y;
		int					m_dest_x, m_dest_y;
		int					frame, m_ant_nb_frame;
		LTexture			*m_ant_sprite;
		SDL_Rect			*m_ant_sprite_clip;
		const static int	M_REDUCE_RATE = 8;
		bool				animate;
		double				angle;
};

#endif
