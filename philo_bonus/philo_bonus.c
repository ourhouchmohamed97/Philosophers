/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:05:36 by mourhouc          #+#    #+#             */
/*   Updated: 2025/05/01 10:47:22 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * launching and creating child process for each philo
 * use fork() for duplicate process
 * use the philo_routine function
 * (error) ? 1 : 0
 */
int	run_simulation(t_philo **philos, t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_philos)
	{
		((*philos) + i)->pid_philo = fork();
		if (((*philos) + i)->pid_philo == -1)
			return (waiting_philo(i, philos));
		else if (((*philos) + i)->pid_philo == 0)
			return (philo_routine((*philos) + i));
		i++;
	}
	return (0);
}

int	init_philo(t_philo **philos, t_data *data)
{
	size_t	i;

	i = 0;
	*philos = malloc((data->num_philos) * sizeof(t_philo));
	if (!philos)
		return (INIT_ERR);
	while (i < data->num_philos)
	{
		if (init_process_philo((*philos) + i, i, data))
			return (INIT_ERR);
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philos;

	if (parse(argc, argv, &data))
		return (err_handler(ARG_ERR));
	data.dinner_start_time = get_time() + (data.num_philos * 42);
	if (init_philo(&philos, &data))
		return (EXIT_FAILURE);
	sem_wait(data.sem_log);
	printf("\n-> Start Simulation:%s %zu%s\n\n", FLASH, (size_t)0, NC);
	sem_post(data.sem_log);
	if (run_simulation(&philos, &data))
		return (err_handler(SIM_ERR));
	stop_simulation(&data, &philos);
	clean_up(&data, &philos);
	return (0);
}
