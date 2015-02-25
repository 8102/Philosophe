/*
** philo.c for philosophe in /home/jibb/rendu
** 
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
** 
** Started on  Wed Feb 25 10:18:39 2015 Jean-Baptiste Grégoire
** Last update Wed Feb 25 16:33:32 2015 Jean-Baptiste Grégoire
*/

#include "philo.h"

void	change_to_eat(t_philo *philo, pthread_mutex_t *stick)
{
  pthread_mutex_lock(stick);
  philo->stick = USED;
  philo->right_philo->stick = USED;
  philo->state = EAT;
}

void	change_to_sleep(t_philo *philo, pthread_mutex_t *stick)
{
  pthread_mutex_lock(stick);
  philo->stick = FREE;
  philo->right_philo->stick = FREE;
  philo->state = SLEEP;
}

void	change_to_think(t_philo *philo, pthread_mutex_t *stick)
{
  pthread_mutex_lock(stick);
  philo->right_philo->stick = USED;
  philo->state = THINK;
}

void			init_mutex(t_philo *philo, pthread_mutex_t *stick)
{
  if (philo->state == THINK)
    {
      pthread_mutex_lock(stick);
      philo->right_philo->stick = USED;
    }
  else if (philo->state == EAT)
    {
      pthread_mutex_lock(stick);
      philo->stick = USED;
      philo->right_philo->stick = USED;
    }
}

pthread_mutex_t	disp = PTHREAD_MUTEX_INITIALIZER;

void			display(t_philo *philo)
{
  char			*state;

  pthread_mutex_lock(&disp);
  if (philo->state == SLEEP)
    state = strdup("sleep");
  else if (philo->state == EAT)
    state = strdup("eat");
  else
    state = strdup("think");
  mvprintw(philo->id, 0, "ID: %d état : %s\n", philo->id, state);
  refresh();
  free(state);
  pthread_mutex_unlock(&disp);
}


void			*start_philo(void *philos)
{
  t_philo		*philo;
  pthread_mutex_t	stick;
  
  philo = (t_philo *)(philos);
  pthread_mutex_init(&stick, NULL);
  init_mutex(philo, &stick);
  while (philo->rice > 0)
    {
      pthread_mutex_unlock(&stick);
      if (philo->state == THINK)
	change_to_eat(philo, &stick);
      else if (philo->state == EAT)
	change_to_sleep(philo, &stick);
      else
	change_to_think(philo, &stick);
      philo->rice -= 1;
      display(philo);
      sleep(1);
    }
  return ((void *)(0));
}
