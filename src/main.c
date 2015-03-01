/*
** main.c for philosophe in /home/jibb/rendu
**
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
**
** Started on  Wed Feb 25 10:18:50 2015 Jean-Baptiste Grégoire
** Last update Sun Mar  1 22:13:46 2015 Hugo Prenat
*/

#include "window.h"

void		init_philo(int nbr_philo)
{
  t_philo	philos[nbr_philo];
  pthread_t	threads[nbr_philo + 2];
  int		i;
  void		*ret;

  i = 0;
  while (i < NUMBER_PHILO)
    {
      philos[i].is_good = 1;
      philos[i].id = i + 1;
      philos[i].rice = NUMBER_CYCLE;
      pthread_mutex_init(&philos[i].stick, NULL);
      philos[i].state = (i == NUMBER_PHILO - 1 ? SLEEP : (i + 2) % 3);
      philos[i].left_philo = &philos[(i == 0 ? NUMBER_PHILO - 1 : i - 1)];
      philos[i].right_philo = &philos[(i == NUMBER_PHILO - 1 ? 0 : i + 1)];
      pthread_create(&threads[i], NULL, &start_philo, &philos[i]);
      i++;
    }
  pthread_create(&threads[i + 1], NULL, &window_display, (void *)(&philos));
  pthread_create(&threads[i + 2], NULL, &window_handle, (void *)(&philos));
  i = 0;
  while (i < NUMBER_PHILO)
    pthread_join(threads[i++], &ret);
  pthread_join(threads[i + 1], &ret);
}

int		run_philo()
{
  if (window_init(0) == (void *)(-1))
    return (-1);
  if (NUMBER_PHILO > 6)
    init_philo(NUMBER_PHILO);
  else
    init_philo(7);
  window_destroy();
  return (0);
}

int		main()
{
  if (run_philo() == -1)
    return (-1);
  return (0);
}
