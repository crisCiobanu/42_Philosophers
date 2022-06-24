/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciobanu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:31:07 by cciobanu          #+#    #+#             */
/*   Updated: 2022/05/12 11:11:40 by cciobanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_safesleep(int tmp)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	while ((now.tv_sec * 1000 + now.tv_usec / 1000)
		- (start.tv_sec * 1000 + start.tv_usec / 1000) < tmp)
	{
		usleep(10);
		gettimeofday(&now, NULL);
	}
}

void	ft_settimes(t_data *data)
{
	struct timeval	tmp;

	gettimeofday(&tmp, NULL);
	data -> starttime = tmp.tv_sec * 1000 + tmp.tv_usec / 1000;
}

long	ft_getdtime(t_data *data)
{
	long			tmp;
	struct timeval	current;

	tmp = data -> starttime;
	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000 + current.tv_usec / 1000) - tmp);
}

long	ft_getptime(t_philo *data)
{
	long			tmp;
	struct timeval	current;

	tmp = data -> starttime;
	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000 + current.tv_usec / 1000) - tmp);
}
