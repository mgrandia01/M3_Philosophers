/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:59:40 by mgrandia          #+#    #+#             */
/*   Updated: 2025/09/27 09:54:48 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	in_s_struct(t_shared *shared_data, pthread_mutex_t *forks, char *argv[])
{
	int	i;

	i = 0;
	shared_data->num_of_philos = ft_atoi(argv[1]);
	shared_data->time_to_die = ft_atoi(argv[2]);
	shared_data->time_to_eat = ft_atoi(argv[3]);
	shared_data->time_to_sleep = ft_atoi(argv[4]);
	shared_data->someone_die = 0;
	shared_data->forks = forks;
	if (argv[5])
		shared_data->num_time_to_eat = ft_atoi(argv[5]);
	else
		shared_data->num_time_to_eat = -1;
	pthread_mutex_init(&shared_data->print_mutex, NULL);
	pthread_mutex_init(&shared_data->death_mutex, NULL);
	while (i < shared_data->num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i ++;
	}
	shared_data->start_time = get_current_time_ms();
}

void	in_philo(t_shared *s_d, t_philo *p, char *argv[], pthread_mutex_t *fork)
{
	int	i;
	int	num_philos;

	i = 0;
	num_philos = ft_atoi(argv[1]);
	while (i < num_philos)
	{
		p[i].id = i + 1;
		p[i].last_meal_time = get_current_time_ms();
		p[i].meals_eaten = 0;
		p[i].shared = s_d;
		p[i].has_left = 0;
		p[i].has_right = 0;
		p[i].left_fork = &fork[i];
		p[i].right_fork = &fork[(i + 1) % num_philos];
		i++;
	}
}
