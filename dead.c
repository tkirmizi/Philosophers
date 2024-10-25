/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:46:56 by tkirmizi          #+#    #+#             */
/*   Updated: 2024/10/25 14:39:20 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dead_print(t_all *all, unsigned int i, int j)
{
	pthread_mutex_lock(&all->p_params->print);
	printf("%u %d died\n", i, j);
	pthread_mutex_unlock(&all->p_params->print);
}

void	*death_and_meal(void *arg)
{
	t_all	*all;
	int		i;
	int		all_ate_enough;
	int		eat_diff;

	i = 0;
	all_ate_enough = 0;
	eat_diff = 0;
	all = (t_all *)arg;
	death_and_meal_2(all, i, all_ate_enough, eat_diff);
	return (NULL);
}

void	death_and_meal_2(t_all *all, int i, int all_ate_enough, int eat_diff)
{
	while (1)
	{
		i = -1;
		all_ate_enough = 1;
		while (++i < all->p_params->n_of_philo)
		{
			pthread_mutex_lock(&all->p_philo[i].eat_lock);
			eat_diff = get_current_time() - all->p_philo[i].last_meal;
			if (eat_diff >= all->p_params->t_die)
			{
				dead_lock_and_print(all, get_current_time()
					- all->p_params->start_time, all->p_philo[i].id);
				pthread_mutex_unlock(&all->p_philo[i].eat_lock);
				return ;
			}
			if (all->p_philo[i].m_count < all->p_params->max_eat)
				all_ate_enough = 0;
			pthread_mutex_unlock(&all->p_philo[i].eat_lock);
		}
		if (all->p_params->max_eat != -1 && all_ate_enough)
		{
			dead_mu_lock(all);
			return ;
		}
	}
}

void	dead_lock_and_print(t_all *all, unsigned int i, int j)
{
	pthread_mutex_lock(&all->p_params->dead_mutex);
	all->p_params->dead = 1;
	pthread_mutex_unlock(&all->p_params->dead_mutex);
	dead_print(all, i, j);
}

void	dead_mu_lock(t_all *all)
{
	pthread_mutex_lock(&all->p_params->dead_mutex);
	all->p_params->dead = 1;
	pthread_mutex_unlock(&all->p_params->dead_mutex);
}
