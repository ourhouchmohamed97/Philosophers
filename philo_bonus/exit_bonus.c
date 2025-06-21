/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:06:04 by mourhouc          #+#    #+#             */
/*   Updated: 2025/06/21 18:27:52 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	waiting_philo(int i, t_philo *philos)
{
	while (i >= 0)
	{
		waitpid(philos[i].pid, NULL, 0);
		i--;
	}
	return (INIT_ERR);
}

void	clean_up(t_data *data, t_philo **philos)
{
	size_t	i;

	if (*philos)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (((*philos) + i)->sem_meals_eaten)
				sem_close(((*philos) + i)->sem_meals_eaten);
			if (((*philos) + i)->sem_last_meal)
				sem_close(((*philos) + i)->sem_last_meal);
			i++;
		}
		free(*philos);
	}
	sem_close(data->sem_forks);
	sem_close(data->sem_print);
	sem_close(data->sem_eat_full);
	sem_close(data->sem_end);
	sem_close(data->sem_set_end);
	sem_unlink("/set_end");
	sem_unlink("/forks");
	sem_unlink("/log");
	sem_unlink("/eat_full");
	sem_unlink("/end");
}

int	err_handler(int type)
{
	if (type == ARG_ERR)
		printf("\033[1;31mError, please enter valid arguments.\033[0m\n\n"
			"  => \033[1;34m./philo <die_time> <eat_time> <sleep_time>"
			" [number_of_time_meals_to_consume]\033[0m\n\n");
	else if (type == SIM_ERR)
		printf("\033[1;31mError with simulation !\033[0m\n\n");
	else if (type == INIT_ERR)
		printf("\033[1;31mError with memory !\033[0m\n\n");
	return (EXIT_FAILURE);
}

void	kill_all_philo(t_data *data, t_philo **philos)
{
	size_t	i;
	int		status;

	i = 0;
	while (i < data->num_philos)
	{
		kill(((*philos) + i)->pid, SIGKILL);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		waitpid(((*philos) + i)->pid, &status, 0);
		i++;
	}
}

