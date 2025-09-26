/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:59:40 by mgrandia          #+#    #+#             */
/*   Updated: 2025/08/31 11:57:04 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_valid_arguments(char *argv[])
{
	int	flag;

	flag = 0;
	if (ft_isnum(argv[1]) != 0 || ft_atoi(argv[1]) > 200
		|| ft_atoi(argv[1]) <= 0)
		flag = printf("Invalid num of philos (%s)\n", argv[1]);
	if (ft_isnum(argv[2]) != 0 || ft_atoi(argv[2]) < 0)
		flag = printf("Invalid time to die (%s)\n", argv[2]);
	if (ft_isnum(argv[3]) != 0 || ft_atoi(argv[3]) < 0)
		flag = printf("Invalid time to eat (%s)\n", argv[3]);
	if (ft_isnum(argv[4]) != 0 || ft_atoi(argv[4]) < 0)
		flag = printf("Invalid time to sleep (%s)\n", argv[4]);
	if (argv[5])
	{
		if (ft_isnum(argv[5]) != 0 || ft_atoi(argv[5]) < 0)
			flag = printf("Invalid number of meals (%s)\n", argv[5]);
	}
	if (flag != 0)
		return (-1);
	return (0);
}

long long	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + (tv.tv_usec / 1000));
}

void	print_text(int text, t_philo *philo, long t)
{
	pthread_mutex_lock(&philo->shared->print_mutex);
	if (text == 0)
		printf("%ld %d has taken a fork\n", t, philo->id);
	else if (text == 1)
		printf("%ld %d is eating\n", t, philo->id);
	else if (text == 2)
		printf("%ld %d is sleeping\n", t, philo->id);
	else
		printf("%ld %d is thinking\n", t, philo->id);
	pthread_mutex_unlock(&philo->shared->print_mutex);
}
