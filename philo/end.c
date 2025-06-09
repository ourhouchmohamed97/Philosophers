/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:13:28 by mourhouc          #+#    #+#             */
/*   Updated: 2025/06/03 13:52:21 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	action_msg(t_philo *philo, int code)
{
	pthread_mutex_lock(&philo->data->print);
	if (is_sim_end(philo->data) && code != DIE)
		code = -1;
	if (code == EAT)
		printf("%s%lld %zu is eating%s\n", GREEN, get_time()
			- philo->data->dinner_start_time, philo->id, NC);
	else if (code == SLEEP)
		printf("%s%lld %zu is sleeping%s\n", BLUE, get_time()
			- philo->data->dinner_start_time, philo->id, NC);
	else if (code == THINK)
		printf("%s%lld %zu is thinking%s\n", YELLOW, get_time()
			- philo->data->dinner_start_time, philo->id, NC);
	else if (code == DIE)
		printf("%s%lld %zu died%s\n", RED, get_time()
			- philo->data->dinner_start_time, philo->id, NC);
	else if (code == TAKE_FORK)
		printf("%s%lld %zu has taken a fork%s\n", CYAN, get_time()
			- philo->data->dinner_start_time, philo->id, NC);
	else if (code == WAIT_FORK)
		printf("%s%lld %zu is waiting for fork%s\n", YELLOW, get_time()
			- philo->data->dinner_start_time, philo->id, NC);
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
