/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:12:19 by mourhouc          #+#    #+#             */
/*   Updated: 2025/06/21 18:27:48 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	action_msg(t_philo *philo, int code)
{
	sem_wait(philo->data->sem_print);
	if (code == EAT)
		printf("%lld %zu is eating\n", get_time()
			- philo->data->dinner_start_time, philo->id);
	else if (code == SLEEP)
		printf("%lld %zu is sleeping\n", get_time()
			- philo->data->dinner_start_time, philo->id);
	else if (code == THINK)
		printf("%lld %zu is thinking\n", get_time()
			- philo->data->dinner_start_time, philo->id);
	else if (code == TAKE_FORK)
		printf("%lld %zu has taken a fork\n", get_time()
			- philo->data->dinner_start_time, philo->id);
	sem_post(philo->data->sem_print);
}

void	synch_start(long long start_time)
{
	while (get_time() < start_time)
		usleep(100);
}

