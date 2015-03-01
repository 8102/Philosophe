/*
** philo.c for philosophe in /home/jibb/rendu
**
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
**
** Started on  Wed Feb 25 10:18:39 2015 Jean-Baptiste Grégoire
** Last update Sun Mar  1 18:17:45 2015 Jean-Baptiste Grégoire
*/

#include "window.h"

void	change_to_eat(t_philo *philo)
{
  pthread_mutex_lock(&philo->right_philo->stick);
  philo->state = EAT;
  philo->rice -= 1;
  printf("ID: %d est dans l'état manger\n", philo->id);
  sleep(CYCLE_EAT);
}

void	change_to_sleep(t_philo *philo)
{
  pthread_mutex_unlock(&philo->right_philo->stick);
  pthread_mutex_unlock(&philo->stick);
  philo->state = SLEEP;
  printf("ID: %d est dans l'état dodo\n", philo->id);
  sleep(CYCLE_SLEEP);
}

void	change_to_think(t_philo *philo)
{
  if (pthread_mutex_trylock(&philo->stick) == 0)
    {
      philo->state = THINK;
      printf("ID: %d est dans l'état réfléchir\n", philo->id);
      sleep(CYCLE_THINK);
    }
  else
    sleep(CYCLE_SLEEP);
}

void			init_mutex(t_philo *philo)
{
  if (philo->state == THINK)
    pthread_mutex_lock(&philo->stick);
  if (philo->state == EAT)
    {
      pthread_mutex_lock(&philo->stick);
      pthread_mutex_lock(&(philo->right_philo->stick));
    }
}

void			*start_philo(void *philos)
{
  t_philo		*philo;

  philo = (t_philo *)(philos);
  init_mutex(philo);
  sleep(1);
  while (philo->rice > 0 && philo->is_good)
    {
      if (philo->state == THINK)
	change_to_eat(philo);
      else if (philo->state == SLEEP)
	change_to_think(philo);
      else
	change_to_sleep(philo);
    }
  return ((void *)(0));
}
