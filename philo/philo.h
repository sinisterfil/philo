/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbayram <hbayram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 22:36:15 by hbayram           #+#    #+#             */
/*   Updated: 2025/02/12 12:48:41 by hbayram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILO 200

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	int				num_of_philo;
	int				num_to_eat;
	int				*dead;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_philosphy
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philo;
}					t_philosophy;

// utils
int					ft_strlen(char *str);
int					ft_atoi(const char *str);
size_t				get_time(void);
void				ft_usleep(size_t milliseconds);
void				print_message(t_philo *philo, int id, char *message);

// init
void				program_init(t_philosophy *program, t_philo *philo);
void				forks_init(pthread_mutex_t *forks, int philo_num);
void				philos_init(t_philosophy *program, t_philo *philo,
						pthread_mutex_t *forks, char **av);

// threads
void				terminator(t_philosophy *program, pthread_mutex_t *forks,
						char *arg);
void				*philosophers_dilemma(void *pointer);
int					mother_thread(t_philosophy *program,
						pthread_mutex_t *forks);

// dilemma
void				overthinking(t_philo *philo);
void				dreaming(t_philo *philo);
void				feasting(t_philo *philo);

// checkup
int					full_belly(t_philo *philo);
int					if_dead(t_philo *philo, size_t time_to_die);
int					anyone_reach_nirvana(t_philo *philo);
void				*to_be_or_not_to_be(void *pointer);

#endif