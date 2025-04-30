/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:12:19 by mourhouc          #+#    #+#             */
/*   Updated: 2025/04/30 16:37:49 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.c"

void	action_msg(t_philo *philo, int code)
{
	sem_wait(philo->data->sem_log);
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
	sem_post(philo->data->sem_log);
}

void	synch_start(long long start_time)
{
	while (get_time() < start_time)
		usleep(100);
}