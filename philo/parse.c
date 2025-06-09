/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:12:26 by mourhouc          #+#    #+#             */
/*   Updated: 2025/06/09 12:30:46 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	strict_atoi(const char *str, int *err)
{
	long	res;
	int		i;

	i = 0;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			*err = 1;
	if (!(str[i] >= '0' && str[i] <= '9'))
		*err = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
		if (res > 2147483647)
			*err = 1;
	}
	if (str[i])
		*err = 1;
	return (res);
}

int	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->print, NULL))
		return (1);
	if (pthread_mutex_init(&data->m_dead, NULL))
		return (1);
	if (pthread_mutex_init(&data->m_last_meal, NULL))
		return (1);
	if (pthread_mutex_init(&data->m_meals_eaten, NULL))
		return (1);
	return (0);
}

// void	manage_forks(t_philo *philo, size_t i)
// {
// 	if (philo->id % 2)
// 	{
// 		philo->left_fork = &philo->data->forks[i];
// 		philo->right_fork = &philo->data->forks[(i + 1)
// 			% philo->data->num_philos];
// 	}
// 	else
// 	{
// 		philo->right_fork = &philo->data->forks[(i + 1)
// 			% philo->data->num_philos];
// 		philo->left_fork = &philo->data->forks[i];
// 	}
// }

/**
 * malloc the data of philos and the data of mutex forks
 * assign the mutex (fork) of the data left and right to each philosopher
 * init the log mutex pointeur to each philo
 * assign all other relevant information
 */
int	init_philo(t_data *data)
{
	size_t	i;

	data->philos = malloc(data->num_philos * sizeof(t_philo));
	data->forks = malloc(data->num_philos * sizeof(pthread_mutex_t));
	if (!data->philos || !data->forks)
		return (1);
	i = 0;
	memset(data->philos, 0, data->num_philos * sizeof(t_philo));
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].meals_eaten = 0;
		data->philos[i].left_fork = &data->philos[i].data->forks[i];
		data->philos[i].right_fork = &data->philos[i].data->forks[(i + 1)
			% data->philos[i].data->num_philos];
		i++;
	}
	return (0);
}

int	parse(int argc, char **argv, t_data *data)
{
	int	err;

	err = 0;
	if (!(argc == 5 || argc == 6))
		return (1);
	data->num_philos = strict_atoi(argv[1], &err);
	data->die_time = strict_atoi(argv[2], &err);
	data->eat_time = strict_atoi(argv[3], &err);
	data->sleep_time = strict_atoi(argv[4], &err);
	data->dead = 0;
	if (argc == 6)
	{
		data->meals2consume = strict_atoi(argv[5], &err);
		if (data->meals2consume == 0)
			err = 1;
	}
	else
		data->meals2consume = 0;
	if (err || data->num_philos <= 0 || data->die_time <= 0 
		|| data->eat_time <= 0 || data->sleep_time <= 0)
		return (ARG_ERR);
	err = init_philo(data);
	if (init_mutex(data))
		return (cleanup_philo(data), 1);
	return (err);
}
