/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:12:01 by mourhouc          #+#    #+#             */
/*   Updated: 2025/06/05 15:29:34 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_philo(t_data *data)
{
	size_t	i;

	i = 0;
	free(data->philos);
	while (i < data->num_philos)
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
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	pthread_mutex_destroy(&data->m_dead);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->m_last_meal);
	pthread_mutex_destroy(&data->m_meals_eaten);
}

int	err_handler(int type)
{
	if (type == ARG_ERR)
		printf("\033[1;31mError, please enter valid arguments.\033[0m\n\n"
			"  => \033[1;34m./philo <die_time> <eat_time> <sleep_time>"
			"[number_of_time_meals_to_consume]\033[0m\n\n");
	else if (type == SIM_ERR)
		printf("\033[1;31mError with simulation !\033[0m\n\n");
	return (EXIT_FAILURE);
}
