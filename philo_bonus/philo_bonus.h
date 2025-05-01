/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:53:07 by mourhouc          #+#    #+#             */
/*   Updated: 2025/05/01 10:48:01 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>     // FLAGS
# include <pthread.h>   // thread
# include <semaphore.h> // semaphore
# include <signal.h>    // kill
# include <stdio.h>     // printf
# include <stdlib.h>    // malloc, free, EXIT_SUCCESS
# include <string.h>    // semaphore
# include <sys/stat.h>  // O_CREAT flag sem
# include <sys/time.h>  // usleep
# include <sys/types.h> // O_CREAT
# include <sys/wait.h>  // waitpid
# include <unistd.h>    // fork

// ================ Struct ================
typedef struct s_data	t_data;

typedef struct s_philo
{
	size_t				id;
	pid_t				pid_philo;
	long long			last_meal;
	size_t				meals_eaten;
	sem_t				*sem_last_meal;
	sem_t				*sem_meals_eaten;
	pthread_t			life_monitor;
	t_data				*data;
}						t_philo;

struct					s_data
{
	sem_t				*sem_forks;
	sem_t				*sem_log;
	sem_t				*sem_end;
	sem_t				*sem_eat_full;
	sem_t				*sem_set_end;
	size_t				num_philos;
	size_t				die_time;
	size_t				dinner_start_time;
	size_t				eat_time;
	size_t				sleep_time;
	size_t				meals_to_consume;
	int					end;
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
# define INIT_ERR 24

// ================ functions bonus ================

// --------------- philo_bonus.c ---------------
int			run_simulation(t_philo **philos, t_data *data);
int			init_philo(t_philo **philos, t_data *data);

// --------------- parse_bonus.c ---------------
int			parse(int argc, char **argv, t_data *data);
long		strict_atoi(const char *str, int *err);
int			init_semaphore(t_data *data);
int			init_process_philo(t_philo *philo, size_t i, t_data *data);

// --------------- time_bonus.c ---------------
void		waiting(long long waitTime);
long long	get_time(void);

// --------------- process_bonus.c ---------------
void		*check_dead_philo(void *philos_ptr);
int			is_sim_end(t_data *data);
void		*check_eat_enough(void *philos_ptr);
void		stop_simulation(t_data *data, t_philo **philos);

// --------------- routine_bonus.c ---------------
int			philo_routine(t_philo *philo);
void		eat(t_philo *philo);
void		rest(t_philo *philo);
void		think(t_philo *philo);
int			solo_philo(t_philo *philo);

// --------------- end_bonus.c ---------------
void		action_msg(t_philo *philo, int code);
void		synch_start(long long start_time);
void		unlink_my_sem(void);

// --------------- exit_bonus.c ---------------
int			waiting_philo(int i, t_philo **philos);
void		clean_up(t_data *data, t_philo **philos);
int			err_handler(int type);
void		kill_all_philo(t_data *data, t_philo **philos);

// --------------- life_bonus.c ---------------
void		*life_monitor(void *philo_ptr);
int			has_philosopher_died(t_philo *philo);
int			eat_enough(t_philo *philo);

// --------------- utils_bonus.c ---------------
size_t		ft_strlen(const char *str);
size_t		nb_digit_id(size_t num);
char		*ft_itoa(size_t id);
char		*get_name_sem(size_t id, char *name);

#endif