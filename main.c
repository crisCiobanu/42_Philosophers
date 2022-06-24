/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciobanu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:27:23 by cciobanu          #+#    #+#             */
/*   Updated: 2022/05/12 11:12:12 by cciobanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_checkcount(t_data *data)
{
	int	iscounted;
	int	i;

	i = -1;
	iscounted = 1;
	while (data -> count && ++i < data -> philo_num)
	{
		if (data -> philos[i].count < data -> count)
			iscounted = 0;
	}
	if (data -> count && iscounted)
	{
		data -> alive = 0;
		return (1);
	}
	return (0);
}

int	ft_isdead(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data -> philo_num)
	{
		if (ft_getdtime(data) - data -> philos[i].lasteaten > data -> ttd)
		{
			pthread_mutex_lock(&(data -> print));
			data -> alive = 0;
			pthread_mutex_unlock(&(data -> print));
			ft_safeprint(&(data -> philos[i]), "died");
			return (1);
		}
	}
	if (ft_checkcount(data))
		return (1);
	return (0);
}

void	ft_launchthreads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		usleep(100);
		pthread_create(data -> philos[i].th, NULL,
			&ft_philo, &(data -> philos[i]));
	}
	while (!ft_isdead(data))
		usleep(100);
	i = -1;
	while (++i < data -> philo_num)
		pthread_join(*(data -> philos[i].th), NULL);
}

void	ft_start(t_data *data)
{
	int	i;

	i = -1;
	ft_settimes(data);
	while (++i < data -> philo_num)
	{
		data -> philos[i].starttime = data -> starttime;
		data -> philos[i].lasteaten = ft_getdtime(data);
	}
	i = -1;
	if (data -> philo_num == 1)
	{
		pthread_create(data -> philos[0].th, NULL,
			&ft_philo1, &(data -> philos[0]));
		pthread_join(*(data -> philos[0].th), NULL);
	}
	else
		ft_launchthreads(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (ft_argscheck(argc, argv))
	{
		ft_printerr();
		return (0);
	}
	data = ft_initdata(argc, argv);
	if (!data)
	{
		printf("Error in initializing data, malloc returned NULL!");
		return (0);
	}
	ft_start(data);
	ft_freemem(data);
	return (0);
}
