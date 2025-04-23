/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:12:01 by mourhouc          #+#    #+#             */
/*   Updated: 2025/04/23 13:12:13 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_philo(t_data *data)
{
	size_t	i;

	i = 0;
	free(data->philos);
	while (i < data->numPhilos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
}

void	clean_up(t_data *data)
{
	size_t	i;

	i = 0;
	free(data->philos);
	while (i < data->numPhilos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	pthread_mutex_destroy(&data->m_dead);
	pthread_mutex_destroy(&data->m_log);
	pthread_mutex_destroy(&data->m_last_meal);
	pthread_mutex_destroy(&data->m_meals_eaten);
}

int		err_handler(int type)
{
	if (type == ARG_ERR)
		printf("\033[1;31mError, please enter valid arguments.\033[0m\n\n"
			"  => \033[1;34m./philo <dieTime> <eatTime> <sleepTime>"
			"[number_of_time_mealsToConsume]\033[0m\n\n");
	else if (type == SIM_ERR)
		printf("\033[1;31mError with simulation !\033[0m\n\n");
	return (EXIT_FAILURE);
}
