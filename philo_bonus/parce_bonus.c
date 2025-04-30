/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:45:51 by mourhouc          #+#    #+#             */
/*   Updated: 2025/04/30 16:05:07 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	strict_atoi(const char *str, int *err)
{
	long	res;
	int		i;

	i = 0;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			*err = 1;
	if (!(str[i] >= '0' && str[i] <= '9'))
		*err = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
		if (res > 2147483647)
			*err = 1;
	}
	if (str[i])
		*err = 1;
	return (res);
}

int	parse(int argc, char **argv, t_data *data)
{
	int	error;

	error = 0;
	if (!(argc == 5 || argc == 6))
		return (INIT_ERR);
	data->numPhilos = strict_atoi(argv[1], &error);
	data->dieTime = strict_atoi(argv[2], &error);
	data->eatTime = strict_atoi(argv[3], &error);
	data->sleepTime = strict_atoi(argv[4], &error);
	data->end = 0;
	data->mealsToConsume = 0;
	if (argc == 6)
	{
		data->mealsToConsume = strict_atoi(argv[5], &error);
		if (data->mealsToConsume == 0)
			error = 1;
	}
	if (error)
		return (INIT_ERR);
	return (init_semaphore(data));
}

int	init_process_philo(t_philo *philo, size_t i, t_data *data)
{
	char	*sem_name_1;
	char	*sem_name_2;

	philo->id = i + 1;
	philo->data = data;
	philo->meals_eaten = 0;
	philo->last_meal = data->dinner_start_time;
	sem_name_1 = get_name_sem(philo->id, "/meals_eaten");
	sem_name_2 = get_name_sem(philo->id, "/last_meal");
	if (!sem_name_1 || !sem_name_2)
		return (INIT_ERR);
	sem_unlink(sem_name_1);
	sem_unlink(sem_name_2);
	philo->sem_meals_eaten = sem_open(sem_name_1, O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (philo->sem_meals_eaten == SEM_FAILED)
		return (INIT_ERR);
	philo->sem_last_meal = sem_open(sem_name_2, O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (philo->sem_last_meal == SEM_FAILED)
		return (INIT_ERR);
	sem_unlink(sem_name_1);
	sem_unlink(sem_name_2);
	free(sem_name_1);
	free(sem_name_2);
	return (0);
}
