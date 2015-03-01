/*
** window_init.c for Philosophes in /home/jibb/rendu/PSU_2014_philo/bonus
**
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
**
** Started on  Fri Feb 27 17:04:28 2015 Jean-Baptiste Grégoire
** Last update Sun Mar  1 12:10:33 2015 Hugo Prenat
*/

#include "window.h"

void			*window_handle(void *p)
{
  SDL_Event		event;
  char			good;
  int			i;
  t_philo		*philos;
  pthread_mutex_t	m;

  good = 1;
  i = 0;
  philos = (t_philo *)(p);
  pthread_mutex_init(&m, NULL);
  while (good)
    {
      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT)
	{
	  pthread_mutex_lock(&m);
	  while (i < NUMBER_PHILO)
	    {
	      philos[i].is_good = 0;
	      i++;
	    }
	  pthread_mutex_unlock(&m);
	  good = 0;
	}
    }
  return (NULL);
}

void			window_display(void *p)
{
  static SDL_Surface	*eat;
  static SDL_Surface	*sleep_img;
  static SDL_Surface	*think;
  SDL_Surface		*screen;
  SDL_Rect		pos;
  int			i;
  t_philo		*philo;

  screen = window_init(1);
  pos.y = 350;
  philo = (t_philo *)(p);
  eat = IMG_Load("bonus/img/eat.png");
  sleep_img = IMG_Load("bonus/img/sleep.png");
  think = IMG_Load("bonus/img/think.png");
  if (!eat || !sleep_img || !think)
    {
      fprintf(stderr, "Error: Can't load image !\n");
      return ;
    }
  while (1)
    {
      i = 0;
      while (i < NUMBER_PHILO || philo[i].is_good)
	{
	  pos.x = philo[i].id * 180 - 170;
	  if (philo[i].state == SLEEP)
	    SDL_BlitSurface(sleep_img, NULL, screen, &pos);
	  else if (philo[i].state == EAT)
	    SDL_BlitSurface(eat, NULL, screen, &pos);
	  else
	    SDL_BlitSurface(think, NULL, screen, &pos);
	  i++;
	}
      return ;
    }
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
