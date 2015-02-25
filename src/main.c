/*
** main.c for philosophe in /home/jibb/rendu
** 
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
** 
** Started on  Wed Feb 25 10:18:50 2015 Jean-Baptiste Grégoire
** Last update Wed Feb 25 16:09:18 2015 Jean-Baptiste Grégoire
*/

#include "philo.h"

void		init_philo()
{
  t_philo	philos[NUMBER_PHILO];
  pthread_t	threads[NUMBER_PHILO];
  int		i;
  void *ret;

  i = 0;
  initscr();
  while (i < NUMBER_PHILO)
    {
      philos[i].id = i + 1;
      philos[i].rice = NUMBER_CYCLE;
      philos[i].stick = FREE;
      if (i == NUMBER_PHILO - 1)
	philos[i].state = SLEEP;
      else
	philos[i].state = (NUMBER_PHILO + 1 - i) % 3;
      philos[i].left_philo = &philos[(i == 0 ? NUMBER_PHILO - 1 : i - 1)];
      philos[i].right_philo = &philos[(i == NUMBER_PHILO - 1 ? 0 : i + 1)];
      pthread_create(&threads[i], NULL, &start_philo, &philos[i]);
      i++;
    }
  i = 0;
  while (i < NUMBER_PHILO)
    {
      pthread_join(threads[i], &ret);
      i++;
    }
  endwin();
}

int		run_philo()
{
  init_philo();
  return (0);
}

int		main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  if (run_philo() == -1)
    return (-1);
  return (0);
}
