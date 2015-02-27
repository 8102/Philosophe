/*
** philo.c for philosophe in /home/jibb/rendu
**
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
**
** Started on  Wed Feb 25 10:18:39 2015 Jean-Baptiste Grégoire
** Last update Fri Feb 27 23:40:57 2015 Jean-Baptiste Grégoire
*/

#include "window.h"

pthread_mutex_t	disp = PTHREAD_MUTEX_INITIALIZER;

void	change_to_eat(t_philo *philo, pthread_mutex_t *stick)
{
  pthread_mutex_lock(stick);
  if (philo->right_philo->stick == USED && philo->right_philo->state == EAT)
    return ;
  philo->stick = USED;
  philo->right_philo->stick = USED;
  philo->state = EAT;
  philo->rice -= 1;
  /* sleep(CYCLE_EAT); */
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
  /* sleep(CYCLE_THINK); */
}

void			init_mutex(t_philo *philo, pthread_mutex_t *stick)
{
  if (philo->state == THINK)
    {
      pthread_mutex_lock(stick);
      philo->stick = USED;
    }
  else if (philo->state == EAT)
    {
      pthread_mutex_lock(stick);
      philo->stick = USED;
      philo->right_philo->stick = USED;
    }
}

void			display(t_philo *philo)
{
  pthread_mutex_lock(&disp);
  move(philo->id - 1, 0);
  clrtoeol();
  if (philo->state == SLEEP)
    mvprintw(philo->id - 1, 0, "ID: %d état : sleep\n", philo->id);
  else if (philo->state == EAT)
    mvprintw(philo->id - 1, 0, "ID: %d état : eat\n", philo->id);
  else
    mvprintw(philo->id - 1, 0, "ID: %d état : think\n", philo->id);
  refresh();
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
      pthread_mutex_lock(&disp);
      window_display(philo);      
      pthread_mutex_unlock(&disp);
    }
  return ((void *)(0));
}
