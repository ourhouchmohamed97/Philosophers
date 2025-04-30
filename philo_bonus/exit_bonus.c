/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:06:04 by mourhouc          #+#    #+#             */
/*   Updated: 2025/04/30 15:05:20 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


int	waiting_philo(int i, t_philo **philos)
{
	while (i > 0)
	{
		waitpid(((*philos) + i)->pid_philo, NULL, 0);
		exit(EXIT_FAILURE);
		i--;
	}
	return (INIT_ERR);
}

void	clean_up(t_data *data, t_philo **philos)
{
	sem_close(data->sem_forks);
	sem_close(data->sem_log);
	sem_close(data->sem_eat_full);
	sem_close(data->sem_end);
	sem_close(data->sem_set_end);
	free(*philos);
}

int	err_handler(int type)
{
	if (type == ARG_ERR)
		printf("\033[1;31mError, please enter valid arguments.\033[0m\n\n"
			"  => \033[1;34m./philo <dieTime> <eatTime> <sleepTime>"
			"[number_of_time_mealsToConsume]\033[0m\n\n");
	else if (type == SIM_ERR)
		printf("\033[1;31mError with simulation !\033[0m\n\n");
	else if (type == INIT_ERR)
		printf("\033[1;31mError with memory !\033[0m\n\n");
	return (EXIT_FAILURE);
}
