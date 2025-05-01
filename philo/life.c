/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:11:31 by mourhouc          #+#    #+#             */
/*   Updated: 2025/05/01 10:50:11 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**hilo_bonus
 * check if a philo is dead
 * => time_since_last_meal > die_time
 */
int	has_philosopher_died(t_philo *philo)
{
	size_t	t_since_last_meal;

	pthread_mutex_lock(&philo->data->m_last_meal);
	t_since_last_meal = get_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->data->m_last_meal);
	if (t_since_last_meal >= philo->data->die_time)
	{
		set_end_sim(philo->data);
		usleep(1000);
		action_msg(philo, DIE);
		return (1);
	}
	return (0);
}

/**
 * check if all philo has eaten enough 1 if all philo is ok
 * else 0
 */
int	sim_over(t_data *data)
{
	size_t	i;
	int		ate_enough;

	ate_enough = 1;
	i = 0;
	while (i < data->num_philos)
	{
		if (has_philosopher_died(&data->philos[i]))
			return (1);
		if (data->meals_to_consume)
		{
			pthread_mutex_lock(&data->m_meals_eaten);
			if (data->philos[i].meals_eaten < data->meals_to_consume)
				ate_enough = 0;
			pthread_mutex_unlock(&data->m_meals_eaten);
		}
		i++;
	}
	if (data->meals_to_consume && ate_enough)
		return (set_end_sim(data), 1);
	else
		return (0);
}

/**
 * check every 0.1ms if the philo is dead or if every philo has eaten enough
 * use the mutex last meal, and die_time to know
 * use
 */
void	*life_monitor(void *data_ptr)
{
	t_data	*data;

	data = (t_data *)data_ptr;
	synch_start(data->dinner_start_time);
	while (!end_sim(data))
	{
		if (sim_over(data))
			break ;
		usleep(1000);
	}
	return (NULL);
}
