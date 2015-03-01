/*
** window_utils.c for philosophe in /home/jibb/rendu/PSU_2014_philo
**
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
**
** Started on  Sun Mar  1 14:46:57 2015 Jean-Baptiste Grégoire
** Last update Sun Mar  1 14:58:34 2015 Jean-Baptiste Grégoire
*/

#include "window.h"

void		display_philo(t_philo *philo, t_img *imgs, SDL_Surface *screen)
{
  SDL_Rect	pos;

  pos.x = philo->id * 180 - 170;
  pos.y = 350;
  if (philo->state == SLEEP)
    SDL_BlitSurface(imgs->sleep_img, NULL, screen, &pos);
  else if (philo->state == EAT)
    SDL_BlitSurface(imgs->eat, NULL, screen, &pos);
  else
    SDL_BlitSurface(imgs->think, NULL, screen, &pos);
}
