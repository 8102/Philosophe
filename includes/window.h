/*
** window.h for philosophe in /home/jibb/rendu/PSU_2014_philo/bonus
**
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
**
** Started on  Fri Feb 27 17:14:11 2015 Jean-Baptiste Grégoire
** Last update Sun Mar  1 14:56:57 2015 Jean-Baptiste Grégoire
*/

#ifndef WINDOW_H_
# define WINDOW_H_

# define WIN_X	1280
# define WIN_Y	800

# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include "philo.h"

typedef struct	s_img
{
  SDL_Surface	*eat;
  SDL_Surface	*sleep_img;
  SDL_Surface	*think;
}		t_img;

void		display_philo(t_philo *philo, t_img *imgs, SDL_Surface *screen);
void		window_destroy();
void		*window_display(void *p);
void		*window_handle(void *p);
SDL_Surface	*window_init(int flag);

#endif /* WINDOW_H_ */
