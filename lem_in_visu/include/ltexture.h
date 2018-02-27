/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ltexture.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 20:33:27 by emarin            #+#    #+#             */
/*   Updated: 2018/02/16 11:29:18 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef L_TEXTURE_H
# define L_TEXTURE_H

# include "../lem_in_visu.h"

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture(SDL_Renderer **renderer);

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool	loadFromFile(std::string path);

		//Creates image from font string
		bool	loadFromRenderedText(TTF_Font *font, char *textureText, SDL_Color textColor);

		//Creates blank texture
		bool	createBlank(int width, int height, SDL_TextureAccess = SDL_TEXTUREACCESS_STREAMING);

		//Deallocates texture
		void	free();

		//Set color modulation
		void	setColor(Uint8 red, Uint8 green, Uint8 blue);

		//Set blending
		void	setBlendMode(SDL_BlendMode blending);

		//Set alpha modulation
		void	setAlpha(Uint8 alpha);

		//Renders texture at given point
		void	render(int x, int y, bool clip_render_dim = true, SDL_Rect *clip = NULL
		, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		void	render(SDL_Rect *renderQuad, SDL_Rect *clip = NULL, double angle = 0.0
		, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		//Set self as render target
		void	setAsRenderTarget();

		//Gets image dimensions
		int		getWidth();
		int		getHeight();

		void	setSize(int width, int height);

		//Pixel manipulators
		bool	lockTexture();
		bool	unlockTexture();
		void	*getPixels();
		void	copyPixels(void *pixels);
		int		getPitch();
		Uint32	getPixel32(unsigned int x, unsigned int y);

	private:
		SDL_Renderer **m_renderer;

		//The actual hardware texture
		SDL_Texture	*mTexture;
		void		*mPixels;
		int			mPitch;

		//Image dimensions
		int			mWidth;
		int			mHeight;
};

#endif
