/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:13:02 by mourhouc          #+#    #+#             */
/*   Updated: 2025/06/21 18:26:41 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waiting(long long waitTime, t_data *data)
{
	long long	time;

	time = get_time() + waitTime;
	while (!is_sim_end(data) && get_time() < time)
		usleep(500);
}

long long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((long long)(current_time.tv_sec * 1000LL) + (current_time.tv_usec
			/ 1000));
}

