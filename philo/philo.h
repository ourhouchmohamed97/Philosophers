/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:10:31 by mourhouc          #+#    #+#             */
/*   Updated: 2025/05/01 10:53:33 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

// ================ Struct ================
typedef struct s_data	t_data;

typedef struct s_philo
{
	size_t				id;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	long long			last_meal;
	t_data				*data;
	size_t				meals_eaten;
}						t_philo;

// struct for contain all the philosophers
struct					s_data
{
	t_philo				*philos;
	pthread_t			philo_life;
	pthread_mutex_t		*forks;
	pthread_mutex_t		m_dead;
	pthread_mutex_t		m_meals_eaten;
	pthread_mutex_t		m_log;
	pthread_mutex_t		m_last_meal;
	size_t				num_philos;
	size_t				die_time;
	size_t				eat_time;
	size_t				sleep_time;
	size_t				meals_to_consume;
	size_t				dinner_start_time;
	int					dead;
};

enum
{
	EAT = 1,
	SLEEP = 2,
	THINK = 3,
	DIE = 4,
	TAKE_FORK = 5,
	WAIT_FORK = 6
};

# define GREEN "\033[0;32m"
# define BLUE "\033[0;36m"
# define YELLOW "\033[0;33m"
# define RED "\033[1;31m"
# define CYAN "\033[0;35m"
# define FLASH "\033[1;93m"
# define NC "\033[0m"

# define ARG_ERR 22
# define SIM_ERR 23

// ================ functions ================

// --------------- parse.c ---------------
int			parse(int argc, char **argv, t_data *data);
long		strict_atoi(const char *str, int *err);
int			init_philo(t_data *data);
int			init_mutex(t_data *data);
void		manage_forks(t_philo *philo, size_t i);

// --------------- exit.c ---------------
void		cleanup_philo(t_data *data);
void		clean_up(t_data *data);
int			err_handler(int type);

// --------------- time.c ---------------
long long	get_time(void);
void		waiting(long long waitTime, t_data *data);

// --------------- philo.c ---------------
int			run_simulation(t_data *data);

// --------------- philo_routine.c ---------------
void		*philo_routine(void *philo_ptr);
void		*solo_philo(t_philo *philo);
void		eat(t_philo *philo);
void		rest(t_philo *philo);
void		think(t_philo *philo);

// --------------- end.c ---------------
void		synch_start(long long start_time);
int			end_sim(t_data *data);
void		set_end_sim(t_data *data);
void		action_msg(t_philo *philo, int code);

// --------------- life.c ---------------
int			has_philosopher_died(t_philo *philo);
int			sim_over(t_data *data);
void		*life_monitor(void	*data_ptr);

#endif