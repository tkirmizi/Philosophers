/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:46:48 by tkirmizi          #+#    #+#             */
/*   Updated: 2024/10/25 11:57:42 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->p_params->n_of_philo)
	{
		all->p_philo[i].id = i + 1;
		all->p_philo[i].dead = 0;
		all->p_philo[i].m_count = 0;
		all->p_philo[i].now_eating = 0;
		all->p_philo[i].last_meal = get_current_time();
		all->p_philo[i].p_params = all->p_params;
		pthread_mutex_init(&(all->p_philo[i].eat_lock), NULL);
	}
}

void	mutex_inits_some(t_all *all)
{
	if (pthread_mutex_init(&all->p_params->print, NULL))
		exit_w_free("error: mutex init failed\n", 1, all);
	if (pthread_mutex_init(&all->p_params->stop, NULL))
		exit_w_free("error: mutex init failed\n", 1, all);
	if (pthread_mutex_init(&all->p_params->dead_mutex, NULL))
		exit_w_free("error: mutex init failed\n", 1, all);
	if (pthread_mutex_init(&all->p_philo->eat_lock, NULL))
		exit_w_free("error: mutex init failed\n", 1, all);
}

void	init_forks(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->p_params->n_of_philo)
	{
		all->p_params->p_forks[i].id = i;
		if (pthread_mutex_init(&(all->p_params->p_forks[i].mutex), NULL))
		{
			while (--i >= 0)
			{
				pthread_mutex_destroy(&(all->p_params->p_forks[i].mutex));
			}
			free(all->p_params->p_forks);
			free(all->p_philo);
			exit_w_free("error: mutex initialization", 1, all);
		}
		i++;
	}
	allocate_forks(all);
}

void	allocate_forks(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->p_params->n_of_philo)
	{
		all->p_philo[i].r_fork = &all->p_params->p_forks[i];
		all->p_philo[i].l_fork = &all->p_params->p_forks[(i + 1)
			% all->p_params->n_of_philo];
		i++;
	}
}
