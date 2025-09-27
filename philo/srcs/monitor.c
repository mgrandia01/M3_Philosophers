/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:59:40 by mgrandia          #+#    #+#             */
/*   Updated: 2025/09/27 11:25:53 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	meals_eaten(t_philo *philo, int i)
{
	int	all_done;

	all_done = 1;
	while (i < philo[0].shared->num_of_philos)
	{
		pthread_mutex_lock(&philo[i].meals_mutex);
		if (philo[i].meals_eaten < philo[i].shared->num_time_to_eat)
			all_done = 0;
		pthread_mutex_unlock(&philo[i].meals_mutex);
		if (!all_done)
			break ;
		i++;
	}
	if (all_done)
	{
		end(&philo[0]);
		return (0);
	}
	return (1);
}

int	check_philosopher_death(t_philo *philo, int i)
{
	size_t	t;

	pthread_mutex_lock(&philo[i].meals_mutex);
	t = get_current_time_ms() - philo[i].last_meal_time;
	pthread_mutex_unlock(&philo[i].meals_mutex);
	if (t >= philo[i].shared->time_to_die)
	{
		condition(&philo[i]);
		return (1);
	}
	return (0);
}

void	*monitor_death(void *arg)
{
	t_philo	*philo;
	int		i;
	int		num;

	philo = (t_philo *)arg;
	num = philo[0].shared->num_of_philos;
	while (1)
	{
		i = 0;
		if (someone_die(&philo[0]) == 1)
			break ;
		if (philo[0].shared->num_time_to_eat != -1)
		{
			if (meals_eaten(philo, i) == 0)
				return (NULL);
		}
		while (i < num)
		{
			if (check_philosopher_death(philo, i) == 1)
				return (NULL);
			i ++;
		}
		usleep(1000);
	}
	return (NULL);
}
