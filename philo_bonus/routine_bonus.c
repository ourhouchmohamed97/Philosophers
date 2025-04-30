/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:08:57 by mourhouc          #+#    #+#             */
/*   Updated: 2025/04/30 16:15:28 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * the daily philo_routine of each philosopher
 * 		- eat()
 * 		- sleep()
 * 		- think()
 *	from here, we are in child process <==> in philosopher body
 *
 */
int	philo_routine(t_philo *philo)
{
	if (philo->data->numPhilos == 1)
		return (solo_philo(philo));
	if (pthread_create(&philo->life_monitor, NULL, &life_monitor, philo))
		return (INIT_ERR);
	synch_start(philo->data->dinner_start_time);
	if (philo->id % 2)
		waiting(philo->data->eatTime);
	while (1)
	{
		eat(philo);
		rest(philo);
		think(philo);
	}
	return (0);
}
