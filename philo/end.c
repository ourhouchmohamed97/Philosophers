/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:13:28 by mourhouc          #+#    #+#             */
/*   Updated: 2025/06/19 21:52:03 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	action_msg(t_philo *philo, int code)
{
	pthread_mutex_lock(&philo->data->print);
	if (is_sim_end(philo->data) && code != DIE)
		code = -1;
	if (code == EAT)
		printf("%lld %zu is eating\n", get_time()
			- philo->data->dinner_start_time, philo->id);
	else if (code == SLEEP)
		printf("%lld %zu is sleeping\n", get_time()
			- philo->data->dinner_start_time, philo->id);
	else if (code == THINK)
		printf("%lld %zu is thinking\n", get_time()
			- philo->data->dinner_start_time, philo->id);
	else if (code == DIE)
		printf("%lld %zu died\n", get_time()
			- philo->data->dinner_start_time, philo->id);
	else if (code == TAKE_FORK)
		printf("%lld %zu has taken a fork\n", get_time()
			- philo->data->dinner_start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

int	is_sim_end(t_data *data)
{
	int	bool_dead;

	bool_dead = 0;
	pthread_mutex_lock(&data->m_dead);
	bool_dead = data->dead;
	pthread_mutex_unlock(&data->m_dead);
	return (bool_dead);
}

void	set_sim_end(t_data *data)
{
	pthread_mutex_lock(&data->m_dead);
	data->dead = 1;
	pthread_mutex_unlock(&data->m_dead);
}

void	synch_start(long long start_time)
{
	while (get_time() < start_time)
	{
		usleep(100);
	}
}
