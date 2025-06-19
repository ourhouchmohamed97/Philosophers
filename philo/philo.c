/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:11:06 by mourhouc          #+#    #+#             */
/*   Updated: 2025/06/19 16:30:26 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	run_simulation(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine,
				&data->philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&data->philo_life, NULL, &life_monitor, data))
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (1);
		i++;
	}
	if (pthread_join(data->philo_life, NULL))
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (parse(argc, argv, &data))
		return (err_handler(ARG_ERR));
	data.dinner_start_time = get_time() + (data.num_philos * 20);
	if (run_simulation(&data))
		return (err_handler(SIM_ERR));
	clean_up(&data);
	return (0);
}
