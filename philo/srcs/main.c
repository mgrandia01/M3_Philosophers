/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:59:40 by mgrandia          #+#    #+#             */
/*   Updated: 2025/09/26 19:18:32 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

char	*one_philo(t_philo *philo)
{
	long int	t;

	t = get_current_time_ms() - (philo->shared->start_time);
	print_text(0, philo, t);
	usleep(philo->shared->time_to_die * 1000);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	long int	t;

	philo = (t_philo *)arg;
	if (philo->shared->num_of_philos == 1)
		return (one_philo(philo));
	if (philo->id % 2 == 0)
		usleep((philo->shared->time_to_eat / 2) * 100);
	while (1)
	{
		if (eating_routine(philo) == 1)
			break ;
		if (is_someone_die(philo) == 1)
			break ;
		t = get_current_time_ms() - (philo->shared->start_time);
		print_text(2, philo, t);
		usleep(philo->shared->time_to_sleep * 1000);
		if (is_someone_die(philo) == 1)
			break ;
		t = get_current_time_ms() - (philo->shared->start_time);
		print_text(3, philo, t);
	}
	leave_forks(philo);
	return (NULL);
}

int	create_threads(t_philo *philo, char *argv[])
{
	static pthread_t	threads[200];
	pthread_t			death_monitor;
	int					i;
	int					num_philos;

	num_philos = ft_atoi(argv[1]);
	i = 0;
	while (i < num_philos)
	{
		if (pthread_create(&threads[i], NULL, &routine, &philo[i]) != 0)
			return (1);
		pthread_detach(threads[i]);
		i ++;
	}
	pthread_create(&death_monitor, NULL, monitor_death, philo);
	pthread_join(death_monitor, NULL);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_shared		shared_data;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];

	if (argc != 5 && argc != 6)
	{
		write(1, "Number of argumens incorrect\n", 30);
		return (0);
	}
	if (check_valid_arguments(argv) != 0)
		return (0);
	in_s_struct(&shared_data, forks, argv);
	in_philo(&shared_data, philos, argv, forks);
	if (create_threads(philos, argv) != 0)
		return (0);
	return (0);
}
