/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:59:40 by mgrandia          #+#    #+#             */
/*   Updated: 2025/09/27 10:37:30 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_a_fork(t_philo *philo)
{
	long	t;

	if (is_someone_die(philo))
			return ;
		
	else if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		philo->has_right = 1;
		t = get_current_time_ms() - (philo->shared->start_time);
		print_text(0, philo, t);
		if (is_someone_die(philo))
		{
			leave_forks(philo);
			return ;
		}
		pthread_mutex_lock(philo->left_fork);
		philo->has_left = 1;
		t = get_current_time_ms() - (philo->shared->start_time);
		print_text(0, philo, t);
		if (is_someone_die(philo))
		{
			leave_forks(philo);
			return ;
		}
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		philo->has_left = 1;
		t = get_current_time_ms() - (philo->shared->start_time);
		print_text(0, philo, t);
		if (is_someone_die(philo))
		{
			leave_forks(philo);
			return ;
		}

		pthread_mutex_lock(philo->right_fork);
		philo->has_right = 1;
		t = get_current_time_ms() - (philo->shared->start_time);
		print_text(0, philo, t);
		if (is_someone_die(philo))
		{
			leave_forks(philo);
			return ;
		}


	}
}

void	leave_forks(t_philo *philo)
{
	if (philo->has_right == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		philo->has_right = 0;
	}
	if (philo->has_left == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		philo->has_left = 0;
	}
}

int	eating_routine(t_philo *philo)
{
	long int	t;
	long int	start;

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
	start = get_current_time_ms();
	while (get_current_time_ms() - start < (long)philo->shared->time_to_eat)
	{
		if (is_someone_die(philo))
			break ;
		usleep(100);
	}
	leave_forks(philo);
	if (philo->shared->num_time_to_eat != -1
		&& philo->meals_eaten >= philo->shared->num_time_to_eat)
	{
		leave_forks(philo);
		return (1);
	}
	return (0);
}
