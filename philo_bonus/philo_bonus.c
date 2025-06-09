/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:05:36 by mourhouc          #+#    #+#             */
/*   Updated: 2025/06/09 15:21:49 by mourhouc         ###   ########.fr       */
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
	int		status;
	pid_t	pid;

	i = 0;
	// Create philosopher processes
	while (i < data->num_philos)
	{
		((*philos) + i)->pid_philo = fork();
		if (((*philos) + i)->pid_philo == -1)
			return (waiting_philo(i, philos)); // handle failed forks
		else if (((*philos) + i)->pid_philo == 0)
			return (philo_routine((*philos) + i)); // child process runs its routine
		i++;
	}
	// Parent process waits for one philosopher to die (exit(1) → status = 256)
	pid = waitpid(-1, &status, 0);
	if (status == 256)
		kill_all_philo(data, philos);
	return (0);
}

// 0000 0001 0000 0000

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

int	init_process_philo(t_philo *philo, size_t i, t_data *data)
{
	char	*sem_name_1;
	char	*sem_name_2;

	philo->id = i + 1;
	philo->data = data;
	philo->meals_eaten = 0;
	philo->last_meal = data->dinner_start_time;
	sem_name_1 = get_name_sem(philo->id, "/meals_eaten");
	sem_name_2 = get_name_sem(philo->id, "/last_meal");
	if (!sem_name_1 || !sem_name_2)
		return (free(sem_name_1), free(sem_name_2), INIT_ERR);
	sem_unlink(sem_name_1);
	sem_unlink(sem_name_2);
	philo->sem_meals_eaten = sem_open(sem_name_1, O_CREAT, S_IRUSR 
			| S_IWUSR, 1);
	if (philo->sem_meals_eaten == SEM_FAILED)
		return (free(sem_name_1), free(sem_name_2), INIT_ERR);
	philo->sem_last_meal = sem_open(sem_name_2, O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (philo->sem_last_meal == SEM_FAILED)
		return (free(sem_name_1), free(sem_name_2), INIT_ERR);
	sem_unlink(sem_name_1);
	sem_unlink(sem_name_2);
	free(sem_name_1);
	free(sem_name_2);
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
	sem_wait(data.sem_print);
	printf("\n-> Philosophers Dinner Begins\n");
	sem_post(data.sem_print);
	if (run_simulation(&philos, &data))
		return (err_handler(SIM_ERR));
	stop_simulation(&data, &philos);
	clean_up(&data, &philos);
	return (0);
}
