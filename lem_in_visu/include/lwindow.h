/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lwindow.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:12:43 by emarin            #+#    #+#             */
/*   Updated: 2018/02/20 19:15:56 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LWINDOW_H
# define LWINDOW_H

# include "../lem_in_visu.h"

extern int SCREEN_WIDTH, SCREEN_HEIGHT;

class LWindow
{
	public:
		//Intializes internals
		LWindow();

		//Creates window
		bool init(std::string str);

		//Creates renderer from internal window
		SDL_Renderer* createRenderer();

		//Handles window events
		void handleEvent(SDL_Event& e, SDL_Renderer **renderer);

		//Deallocates internals
		void free();

		//Window dimensions
		int getWidth();
		int getHeight();

		SDL_Window	*getWindow();

		//Window focii
		bool hasMouseFocus();
		bool hasKeyboardFocus();
		bool isMinimized();

	private:
		//Window data
		SDL_Window* mWindow;

		//Window dimensions
		int mWidth;
		int mHeight;

		//Window focus
		bool mMouseFocus;
		bool mKeyboardFocus;
		bool mFullScreen;
		bool mMinimized;
};

#endif
