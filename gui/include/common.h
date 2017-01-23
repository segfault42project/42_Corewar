/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 13:36:35 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/23 17:31:26 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <SDL2/SDL.h>
# include <sys/types.h>
# include <SDL2/SDL_ttf.h>
# include "../libft/includes/libft.h"

#define ERROR (-1)
#define INIT_VIDEO_ERROR (1)
#define CREATE_WINDOW_ERROR (2)

#define WIDTH 2160
#define HEIGHT 1080
#define MEM_SIZE 4096

uint8_t	g_memory[MEM_SIZE];

typedef struct		s_win
{
	SDL_Window		*win;
	SDL_Renderer	*render;
}					t_win;

typedef struct		s_font
{
	uint8_t			font_size;
	TTF_Font		*font;
	SDL_Color		text_color;
	SDL_Surface		*text;
	SDL_Texture		*texture;
	SDL_Rect		text_rect;
}					t_font;

void	gui();
void	error(uint8_t error);
void	create_window(t_win *win);
void	close_window(t_win *win, int8_t error);
void	sdl_clear(t_win *win, uint8_t r, uint8_t g, uint8_t b);
/*
** font.c
*/
void	init_ttf(t_win *win, t_font *font);
void	draw_text(t_font *font, t_win *win, char *str);

void	draw_memory(t_win *win, t_font *font);

#endif
