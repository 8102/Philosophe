/*
m** philo.h for philosophe in /home/jibb/rendu/PSU_2014_philo
**
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
**
** Started on  Wed Feb 25 10:21:52 2015 Jean-Baptiste Grégoire
** Last update Thu Feb 26 16:54:53 2015 Hugo Prenat
*/

#ifndef PHILOSOPHE_H_
# define PHILOSOPHE_H_

# include <pthread.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <strings.h>
# include <unistd.h>
# include <string.h>
# include <curses.h>

# define NUMBER_PHILO	7 // attention à la modification de cet maccro
# define CYCLE_EAT	1
# define CYCLE_THINK	1
# define NUMBER_CYCLE	1500

enum	e_state
  {
    SLEEP = 0,
    THINK,
    EAT
  };

enum	e_stick
  {
    FREE = 0,
    USED
  };

typedef struct s_philo	t_philo;

struct		s_philo
{
  int		id;
  int		rice;
  enum e_state	state;
  int8_t	stick;
  t_philo	*left_philo;
  t_philo	*right_philo;
};

void		*start_philo(void *philos);

#endif /* PHILOSOPHE_H_ */
