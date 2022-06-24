/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciobanu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:36:37 by cciobanu          #+#    #+#             */
/*   Updated: 2022/05/11 15:37:28 by cciobanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_freemem(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data -> philo_num)
		free(data -> philos[i].th);
	free(data -> philos);
	free(data -> forks);
	free(data);
}

void	ft_destroymutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data -> philo_num)
	{
		pthread_mutex_destroy(&(data -> forks[i]));
	}
	pthread_mutex_destroy(&(data -> print));
	pthread_mutex_destroy(&(data -> alivechecker));
}

void	ft_printerr(void)
{
	printf("****************************\n");
	printf("*  Not valid arguments     *\n");
	printf("*  1 - Time to die         *\n");
	printf("*  2 - Time to eat         *\n");
	printf("*  3 - Time to sleep       *\n");
	printf("*  4 - Number of meals(*)  *\n");
	printf("****************************\n");
}

void	ft_safeprint(t_philo *philo, char *str)
{
	pthread_mutex_lock(&(philo -> data -> print));
	printf("%ld %d %s\n", ft_getptime(philo), philo -> index, str);
	pthread_mutex_unlock(&(philo -> data -> print));
}

int	ft_checkalive(t_data *data)
{
	int	res;

	res = 1;
	pthread_mutex_lock(&(data ->alivechecker));
	if (data -> alive == 0)
		res = 0;
	pthread_mutex_unlock(&(data -> alivechecker));
	return (res);
}
