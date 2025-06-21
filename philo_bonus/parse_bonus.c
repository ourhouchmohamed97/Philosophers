/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:45:51 by mourhouc          #+#    #+#             */
/*   Updated: 2025/06/21 18:28:01 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	init_semaphore(t_data *data)
{
	sem_unlink("/set_end");
	sem_unlink("/forks");
	sem_unlink("/log");
	sem_unlink("/eat_full");
	sem_unlink("/end");
	data->sem_forks = sem_open("/forks", O_CREAT, 0600,
			data->num_philos);
	if (data->sem_forks == SEM_FAILED)
		return (INIT_ERR);
	data->sem_print = sem_open("/log", O_CREAT, 0600, 1);
	if (data->sem_print == SEM_FAILED)
		return (INIT_ERR);
	data->sem_eat_full = sem_open("/eat_full", O_CREAT, 0600,
			data->num_philos);
	if (data->sem_eat_full == SEM_FAILED)
		return (INIT_ERR);
	data->sem_end = sem_open("/end", O_CREAT, 0600,
			data->num_philos);
	if (data->sem_end == SEM_FAILED)
		return (INIT_ERR);
	data->sem_set_end = sem_open("/set_end", O_CREAT, 0600, 1);
	if (data->sem_set_end == SEM_FAILED)
		return (INIT_ERR);
	return (0);
}

int	parse(int argc, char **argv, t_data *data)
{
	int	error;

	error = 0;
	if (!(argc == 5 || argc == 6))
		return (ARG_ERR);
	data->num_philos = strict_atoi(argv[1], &error);
	data->die_time = strict_atoi(argv[2], &error);
	data->eat_time = strict_atoi(argv[3], &error);
	data->sleep_time = strict_atoi(argv[4], &error);
	data->end = 0;
	data->meals2consume = 0;
	if (argc == 6)
	{
		data->meals2consume = strict_atoi(argv[5], &error);
		if (data->meals2consume == 0)
			error = 1;
	}
	else
		data->meals2consume = 0;
	if (error || data->num_philos <= 0 || data->die_time <= 0 
		|| data->eat_time <= 0 || data->sleep_time <= 0)
		return (ARG_ERR);
	return (init_semaphore(data));
}

