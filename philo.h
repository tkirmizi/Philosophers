/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:43:00 by tkirmizi          #+#    #+#             */
/*   Updated: 2024/10/25 14:52:23 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct s_all
{
	struct s_params	*p_params;
	struct s_philo	*p_philo;
	struct s_fork	*p_fork;
}	t_all;

typedef struct s_params
{
	int				n_of_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				max_eat;
	int				eat_done;
	unsigned int	start_time;
	int				dead;
	pthread_mutex_t	dead_mutex;
	struct s_fork	*p_forks;
	pthread_mutex_t	print;
	pthread_mutex_t	stop;
}			t_params;

typedef struct s_philo
{
	pthread_t		th_id;

	int				id;
	int				dead;
	int				m_count;
	int				now_eating;
	unsigned int	last_meal;
	pthread_mutex_t	eat_lock;
	struct s_params	*p_params;
	struct s_fork	*r_fork;
	struct s_fork	*l_fork;
}			t_philo;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
}	t_fork;

int				ft_atoi(const char *str);
void			handle_arguments(int ac, char **av, t_all *all);
void			philo_starter(t_all *all);
void			allocate_forks(t_all *all);
void			init_forks(t_all *all);
unsigned int	get_current_time(void);
void			thread_create(t_all *all);
void			exit_w_free(char *str, int i, t_all *all);
void			*routine(void *arg);
void			think_philo(t_philo *philo);
void			eat_philo(t_philo *philo);
void			sleep_philo(t_philo *philo);
void			sleep_philo(t_philo *philo);
void			print_status(t_philo *philo, char *status);
void			ft_sleep(unsigned int ms);
int				meal_limit_reached(t_philo *philo);
void			all_clean(t_all *all);
void			mutex_inits_some(t_all *all);
void			init_philos(t_all *all);
void			one_philo(t_all *all);
void			*routine_for_alone(void *arg);
void			*death_and_meal(void *arg);
void			eat_philo_2(t_philo *philo, int is_dead);
void			dead_mu_lock(t_all *all);
void			death_and_meal_2(t_all *all, int i,
					int all_ate_enough, int eat_diff);
void			dead_lock_and_print(t_all *all, unsigned int i, int j);
