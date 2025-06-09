/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:12:19 by mourhouc          #+#    #+#             */
/*   Updated: 2025/06/03 13:53:11 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	action_msg(t_philo *philo, int code)
{
	sem_wait(philo->data->sem_print);
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
	sem_post(philo->data->sem_print);
}

void	synch_start(long long start_time)
{
	while (get_time() < start_time)
		usleep(100);
}

void	unlink_my_sem(void)
{
	sem_unlink("/set_end");
	sem_unlink("/forks");
	sem_unlink("/log");
	sem_unlink("/eat_full");
	sem_unlink("/end");
}
