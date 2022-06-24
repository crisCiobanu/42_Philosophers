/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciobanu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:32:36 by cciobanu          #+#    #+#             */
/*   Updated: 2022/05/11 15:35:59 by cciobanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_takingforks(t_philo *philo)
{
	if (philo -> data -> alive == 0)
		return (1);
	pthread_mutex_lock(philo->left);
	if (philo -> data -> alive == 0)
		return (1);
	ft_safeprint(philo, "has taken a fork");
	if (philo -> data -> alive == 0)
	{
		pthread_mutex_unlock(philo -> left);
		return (1);
	}
	pthread_mutex_lock(philo->right);
	if (philo -> data -> alive == 0)
		return (1);
	ft_safeprint(philo, "has taken a fork");
	if (philo -> data -> alive == 0)
		return (1);
	ft_safeprint(philo, "is eating");
	philo->lasteaten = ft_getptime(philo);
	ft_safesleep(philo -> data -> tte);
	pthread_mutex_unlock(philo -> right);
	pthread_mutex_unlock(philo -> left);
	return (0);
}

int	ft_sleeping(t_philo *philo)
{
	if (philo -> data -> alive == 0)
		return (1);
	ft_safeprint(philo, "is sleeping");
	ft_safesleep(philo -> data -> tts);
	return (0);
}

int	ft_thinking(t_philo *philo)
{
	if (philo -> data -> alive == 0)
		return (1);
	ft_safeprint(philo, "is thinking");
	return (0);
}

void	*ft_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo -> index % 2 == 1)
		ft_safesleep(1);
	while (philo -> data -> alive)
	{
		if (ft_takingforks(philo))
			return (NULL);
		if (philo -> data -> count)
			philo -> count++;
		if (ft_sleeping(philo))
			return (NULL);
		if (ft_thinking(philo))
			return (NULL);
	}
	return (NULL);
}

void	*ft_philo1(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	printf("%ld %d has taken a fork\n", ft_getptime(philo), philo -> index);
	if (pthread_mutex_lock(philo->right))
		return (NULL);
	usleep(philo -> data -> ttd * 1000);
	printf("%ld %d died\n", ft_getptime(philo), philo -> index);
	return (NULL);
}
