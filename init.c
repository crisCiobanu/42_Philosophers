/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciobanu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:38:30 by cciobanu          #+#    #+#             */
/*   Updated: 2022/05/11 16:03:28 by cciobanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_argscheck(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (1);
	i = 0;
	while (argv[++i])
	{
		if (ft_isnumber(argv[i]))
			return (2);
	}
	return (0);
}

void	ft_initforks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data ->philo_num)
		pthread_mutex_init(&(data -> forks[i]), NULL);
	pthread_mutex_init(&(data ->print), NULL);
	pthread_mutex_init(&(data -> alivechecker), NULL);
}

int	ft_initphilo(t_data *data, int i, int nbr)
{
	data -> philos[i].index = i;
	data -> philos[i].th = malloc(sizeof(pthread_t));
	if (!(data -> philos[i].th))
		return (1);
	data -> philos[i].left = &(data -> forks[i]);
	data -> philos[i].right = &(data -> forks[(i + 1) % nbr]);
	data -> philos[i].data = data;
	data -> philos[i].count = 0;
	return (0);
}

void	ft_initpartdata(t_data *data, int argc, char **argv)
{
	data -> philo_num = ft_atoi(argv[1]);
	data -> alive = 1;
	data -> ttd = (time_t)(ft_atoi(argv[2]));
	data -> tte = (time_t)(ft_atoi(argv[3]));
	data -> tts = (time_t)(ft_atoi(argv[4]));
	data -> count = 0;
	if (argc == 6)
		data -> count = ft_atoi(argv[5]);
}

t_data	*ft_initdata(int argc, char **argv)
{
	t_data	*data;
	int		nbr;
	int		i;

	nbr = ft_atoi(argv[1]);
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	ft_initpartdata(data, argc, argv);
	data -> forks = malloc(sizeof(pthread_mutex_t) * nbr);
	data -> philos = malloc(sizeof(t_philo) * nbr);
	if (!(data -> forks) || !(data -> philos))
		return (NULL);
	i = -1;
	while (++i < nbr)
	{
		if (ft_initphilo(data, i, nbr))
			return (NULL);
	}
	ft_initforks(data);
	return (data);
}
