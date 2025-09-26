/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:59:40 by mgrandia          #+#    #+#             */
/*   Updated: 2025/08/31 11:57:04 by mgrandia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_convert(const char *nptr, int i)
{
	int	n;
	int	res;

	n = 0;
	res = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = nptr[i] - '0';
		res = (res * 10) + n;
		i ++;
	}
	return (res);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sig;
	int	res;

	i = 0;
	sig = 1;
	res = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\v'
		|| nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\f')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sig = -1;
		i ++;
	}
	if (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = ft_convert(nptr, i);
		return (res * sig);
	}
	return (0);
}

int	ft_isnum(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] < '0' || argv[i] > '9')
			return (1);
		i ++;
	}
	return (0);
}
