/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciobanu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:22:55 by cciobanu          #+#    #+#             */
/*   Updated: 2022/05/11 16:26:18 by cciobanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "philo.h"
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				index;
	int				count;

	time_t			lasteaten;
	long			starttime;
	pthread_t		*th;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				philo_num;
	int				alive;
	int				count;
	long			starttime;

	time_t			ttd;
	time_t			tte;
	time_t			tts;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	alivechecker;
}	t_data;

void	ft_settimes(t_data *data);
long	ft_getdtime(t_data *data);
long	ft_getptime(t_philo *data);
void	ft_safeprint(t_philo *philo, char *str);
void	*ft_philo(void *data);
void	*ft_philo1(void *data);
void	ft_freemem(t_data *data);
void	ft_destroymutexes(t_data *data);
void	ft_printerr(void);
void	ft_safeprint(t_philo *philo, char *str);
void	ft_safesleep(int tmp);
int		ft_checkalive(t_data *data);

int		ft_atoi(char *str);
int		ft_isnumber(char *nbr);
int		ft_argscheck(int argc, char **argv);
t_data	*ft_initdata(int argc, char **argv);

#endif
