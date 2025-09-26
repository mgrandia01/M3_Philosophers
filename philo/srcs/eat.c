/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:59:40 by mgrandia          #+#    #+#             */
/*   Updated: 2025/09/26 17:45:13 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_a_fork(t_philo *philo)
{
	long	t;

	pthread_mutex_lock(philo->right_fork);
	t = get_current_time_ms() - (philo->shared->start_time);
	print_text(0, philo, t);
	pthread_mutex_lock(philo->left_fork);
	t = get_current_time_ms() - (philo->shared->start_time);
	print_text(0, philo, t);
}

void	leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

int	eating_routine(t_philo *philo)
{
	long int	t;

	if (is_someone_die(philo) == 1)
		return (1);
	take_a_fork(philo);
	if (is_someone_die(philo) == 1)
	{
		leave_forks(philo);
		return (1);
	}
	t = get_current_time_ms() - (philo->shared->start_time);
	print_text(1, philo, t);
	pthread_mutex_lock(&philo->meals_mutex);
	philo->last_meal_time = get_current_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_mutex);
	usleep(philo->shared->time_to_eat * 1000);
	leave_forks(philo);
	if (philo->shared->num_time_to_eat != -1
		&& philo->meals_eaten >= philo->shared->num_time_to_eat)
		return (1);
	return (0);
}
