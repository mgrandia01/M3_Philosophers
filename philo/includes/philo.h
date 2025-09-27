/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:59:40 by mgrandia          #+#    #+#             */
/*   Updated: 2025/09/27 09:54:09 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_shared
{
	int				num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_time_to_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	int				someone_die;
	long			start_time;
}	t_shared;

typedef struct s_philo
{
	int					id;
	long				last_meal_time;
	int					meals_eaten;
	pthread_mutex_t		meals_mutex;
	t_shared			*shared;
	int			has_left;
	int			has_right;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
}	t_philo;

//--------phhilo_utils.c----------
int			check_valid_arguments(char *argv[]);
long long	get_current_time_ms(void);
void		print_text(int text, t_philo *philo, long t);

//-------util_atoi.c---------
int			ft_atoi(const char *nptr);
int			ft_isnum(char *argv);

//-------initialization----------
void		in_s_struct(t_shared *s, pthread_mutex_t *f, char *argv[]);
void		in_philo(t_shared *s, t_philo *p, char *a[], pthread_mutex_t *f);

//-------monitor.c-----------
int			is_someone_die(t_philo *philo);
void		condition(t_philo *philo);
void		end(t_philo *philo);
int			someone_die(t_philo *philo);
int			meals_eaten(t_philo *philo, int i);
void		*monitor_death(void *arg);

//---------eat.c----------------
void		take_a_fork(t_philo *philo);
void		leave_forks(t_philo *philo);
int			eating_routine(t_philo *philo);
#endif
