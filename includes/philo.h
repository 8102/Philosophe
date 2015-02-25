/*
** philo.h for philosophe in /home/jibb/rendu/PSU_2014_philo
** 
** Made by Jean-Baptiste Grégoire
** Login   <jibb@epitech.net>
** 
** Started on  Wed Feb 25 10:21:52 2015 Jean-Baptiste Grégoire
** Last update Wed Feb 25 10:27:19 2015 Jean-Baptiste Grégoire
*/

#ifndef PHILOSOPHE_H_
# define PHILOSOPHE_H_

# include <pthread.h>
# include <stddef.h>

typedef struct	s_philo
{
  int		id;
  int8_t	left_stick;
  int8_t	right_stick;
}		t_philo;

#endif /* PHILOSOPHE_H_ */
