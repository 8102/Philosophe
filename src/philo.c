/*
** philo.c for philosophe in /home/jibb/rendu
**
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
**
** Started on  Wed Feb 25 10:18:39 2015 Jean-Baptiste Grégoire
** Last update Sun Mar  1 15:40:01 2015 Hugo Prenat
*/

#include "window.h"

void	change_to_eat(t_philo *philo)
{
  pthread_mutex_lock(&philo->stick);
  if (pthread_mutex_trylock(&philo->right_philo->stick))
    {
      //      printf("JE N'ACCEPTE PAS\n\n\n");
      pthread_mutex_unlock(&philo->stick);
      return ;
    }
  philo->state = EAT;
  philo->rice -= 1;
  printf("ID: %d état : eat\n", philo->id);
  sleep(CYCLE_EAT);
  pthread_mutex_unlock(&philo->stick);
  pthread_mutex_unlock(&philo->right_philo->stick);
}

void	change_to_sleep(t_philo *philo)
{
  if (philo->state != EAT)
    return ;
  philo->state = SLEEP;
  printf("ID: %d état : sleep\n", philo->id);
}

void	change_to_think(t_philo *philo)
{
  pthread_mutex_lock(&philo->stick);
  philo->state = THINK;
  printf("ID: %d état : think\n", philo->id);
  sleep(CYCLE_THINK);
  pthread_mutex_unlock(&philo->stick);
}

void			*start_philo(void *philos)
{
  t_philo		*philo;

  philo = (t_philo *)(philos);
  while (philo->rice > 0 && philo->is_good)
    {
      if (philo->state == THINK || philo->state == SLEEP)
	change_to_eat(philo);
      else if (philo->state == SLEEP)
	change_to_think(philo);
      else
	change_to_sleep(philo);
    }
  return ((void *)(0));
}
