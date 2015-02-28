/*
** philo.c for philosophe in /home/jibb/rendu
**
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
**
** Started on  Wed Feb 25 10:18:39 2015 Jean-Baptiste Grégoire
** Last update Sat Feb 28 18:52:29 2015 Jean-Baptiste Grégoire
*/

#include "window.h"

pthread_mutex_t	disp = PTHREAD_MUTEX_INITIALIZER;

void	change_to_eat(t_philo *philo)
{
  pthread_mutex_lock(&philo->stick);
  pthread_mutex_lock(&philo->right_philo->stick);
  philo->state = EAT;
  philo->rice -= 1;
  sleep(CYCLE_EAT);
  pthread_mutex_unlock(&philo->stick);
  pthread_mutex_unlock(&philo->right_philo->stick);
}

void	change_to_sleep(t_philo *philo)
{
  philo->state = SLEEP;
}

void	change_to_think(t_philo *philo)
{
  pthread_mutex_lock(&philo->stick);
  philo->state = THINK;
  sleep(CYCLE_THINK);
  pthread_mutex_unlock(&philo->stick);
}

void			display(t_philo *philo)
{
  pthread_mutex_lock(&disp);
  if (philo->state == SLEEP)
    printf("ID: %d état : sleep\n", philo->id);
  else if (philo->state == EAT)
    printf("ID: %d état : eat\n", philo->id);
  else
    printf("ID: %d état : think\n", philo->id);
  pthread_mutex_unlock(&disp);
}


void			*start_philo(void *philos)
{
  t_philo		*philo;

  philo = (t_philo *)(philos);
  while (philo->rice > 0 && philo->is_good)
    {
      if (philo->state == THINK)
	change_to_eat(philo);
      else if (philo->state == EAT)
	change_to_sleep(philo);
      else
	change_to_think(philo);
      pthread_mutex_lock(&disp);
      window_display(philo);
      pthread_mutex_unlock(&disp);
      /* display(philo); */
    }
  return ((void *)(0));
}
