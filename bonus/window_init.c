/*
** window_init.c for Philosophes in /home/jibb/rendu/PSU_2014_philo/bonus
** 
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
** 
** Started on  Fri Feb 27 17:04:28 2015 Jean-Baptiste Grégoire
** Last update Sat Feb 28 17:59:13 2015 Jean-Baptiste Grégoire
*/

#include "window.h"

void		window_handle()
{
  SDL_Event	event;
  char		good;

  good = 1;
  while (good)
    {
      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT)
	good = 0;
    }
}

void		window_display(t_philo *philo)
{
  SDL_Surface	*tmp;
  SDL_Surface	*screen;
  SDL_Rect	pos;

  screen = window_init(1);
  pos.x = philo->id * 165 - 100;
  pos.y = 350;
  tmp = SDL_CreateRGBSurface(SDL_HWSURFACE, 150, 100, 32, 0, 0, 0, 0);
  if (philo->state == SLEEP)
    SDL_FillRect(tmp, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
  else if (philo->state == EAT)
    SDL_FillRect(tmp, NULL, SDL_MapRGB(screen->format, 0, 255, 0));
  else
    SDL_FillRect(tmp, NULL, SDL_MapRGB(screen->format, 0, 0, 255));
  SDL_BlitSurface(tmp, NULL, screen, &pos);
  SDL_Flip(screen);
}

SDL_Surface		*window_init(int flag)
{
  static SDL_Surface	*screen = NULL;
  SDL_Surface		*background;

  if (flag == 1)
    return (screen);
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)
    {
      fprintf(stderr, "SDL initialisation error\n");
      return ((SDL_Surface *)(-1));
    }
  screen = SDL_SetVideoMode(WIN_X, WIN_Y, 32, SDL_HWSURFACE);
  background = IMG_Load("bonus/img/background.jpg");
  if (!screen || !background)
    {
      fprintf(stderr, "Error: can't create the window\n");
      return ((SDL_Surface *)(-1));
    }
  SDL_WM_SetCaption("Les philosophes", NULL);
  SDL_BlitSurface(background, NULL, screen, NULL);
  SDL_Flip(screen);
  return (NULL);
}

void		window_destroy()
{
  SDL_Quit();
}
