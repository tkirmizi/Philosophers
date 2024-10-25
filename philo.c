/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:46:51 by tkirmizi          #+#    #+#             */
/*   Updated: 2024/10/25 11:57:57 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_all *all)
{
	if (pthread_create(&all->p_philo[0].th_id, NULL,
			routine_for_alone, &all->p_philo[0]))
		exit_w_free("error: create thread\n", 1, all);
	pthread_join(all->p_philo[0].th_id, NULL);
}

void	philo_starter(t_all *all)
{
	int	i;

	i = -1;
	all->p_params->eat_done = 0;
	all->p_philo = malloc(all->p_params->n_of_philo * sizeof(t_philo));
	if (!all->p_philo)
		exit_w_free("error: malloc\n", 1, all);
	all->p_params->p_forks = malloc(all->p_params->n_of_philo * sizeof(t_fork));
	if (!all->p_params->p_forks)
		exit_w_free("error: malloc\n", 1, all);
	mutex_inits_some(all);
	init_forks(all);
	init_philos(all);
}
