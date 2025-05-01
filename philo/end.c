/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:13:28 by mourhouc          #+#    #+#             */
/*   Updated: 2025/05/01 10:59:16 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	action_msg(t_philo *philo, int code)
{
	pthread_mutex_lock(&philo->data->m_log);
	if (end_sim(philo->data) && code != DIE)
		code = -1;
	if (code == EAT)
		printf("%s%09lld %zu is eating%s\n", GREEN, get_time()
			- philo->data->dinner_start_time, philo->id, NC);
	else if (code == SLEEP)
		printf("%s%09lld %zu is sleeping%s\n", BLUE, get_time()
			- philo->data->dinner_start_time, philo->id, NC);
	else if (code == THINK)
		printf("%s%09lld %zu is thinking%s\n", YELLOW, get_time()
			- philo->data->dinner_start_time, philo->id, NC);
	else if (code == DIE)
		printf("%s%09lld %zu died%s\n", RED, get_time()
			- philo->data->dinner_start_time, philo->id, NC);
	else if (code == TAKE_FORK)
		printf("%s%09lld %zu has taken a fork%s\n", CYAN, get_time()
			- philo->data->dinner_start_time, philo->id, NC);
	else if (code == WAIT_FORK)
		printf("%s%09lld %zu is wating for fork%s\n", YELLOW, get_time()
			- philo->data->dinner_start_time, philo->id, NC);
	pthread_mutex_unlock(&philo->data->m_log);
}

int	end_sim(t_data *data)
{
	int	bool_dead;

	bool_dead = 0;
	pthread_mutex_lock(&data->m_dead);
	bool_dead = data->dead;
	pthread_mutex_unlock(&data->m_dead);
	return (bool_dead);
}

void	set_end_sim(t_data *data)
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
