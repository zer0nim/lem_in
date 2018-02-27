/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:12:43 by emarin            #+#    #+#             */
/*   Updated: 2018/02/16 14:04:51 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOM_H
# define ROOM_H

# include "../lem_in_visu.h"
# include "ltexture.h"
# include "camera.h"

class Room
{
    public:
		Room(LTexture *title, LTexture *room_texture);

		void		render(Camera *camera);

		void		setPos(int x, int y);

		LTexture	*getTitle();

		int			getX();
		int			getY();

    private:
		int m_pos_x, m_pos_y;
		LTexture *m_room_texture;
		LTexture *m_title;
};

#endif
