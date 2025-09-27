/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 11:24:50 by mgrandia          #+#    #+#             */
/*   Updated: 2025/09/27 11:26:36 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_someone_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->death_mutex);
	if (philo->shared->someone_die)
	{
		pthread_mutex_unlock(&philo->shared->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->shared->death_mutex);
	return (0);
}

void	condition(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->print_mutex);
	printf("%lld", get_current_time_ms()
		- philo->shared->start_time);
	printf(" %d died\n", philo->id);
	pthread_mutex_unlock(&philo->shared->print_mutex);
	pthread_mutex_lock(&philo->shared->death_mutex);
	philo->shared->someone_die = 1;
	pthread_mutex_unlock(&philo->shared->death_mutex);
}

void	end(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->death_mutex);
	philo->shared->someone_die = 1;
	pthread_mutex_unlock(&philo->shared->death_mutex);
}

int	someone_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->death_mutex);
	if (philo->shared->someone_die)
	{
		pthread_mutex_unlock(&philo->shared->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->shared->death_mutex);
	return (0);
}
