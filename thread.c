/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:46:53 by tkirmizi          #+#    #+#             */
/*   Updated: 2024/10/25 14:38:06 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_create(t_all *all)
{
	pthread_t	monitor;
	int			i;

	all->p_params->dead = 0;
	i = -1;
	all->p_params->start_time = get_current_time();
	if (all->p_params->n_of_philo == 1)
		one_philo(all);
	else
	{
		if (pthread_create(&monitor, NULL, death_and_meal, all))
			exit_w_free("error: create monitor thread\n", 1, all);
		while (++i < all->p_params->n_of_philo)
		{
			if (pthread_create(&all->p_philo[i].th_id, NULL, routine,
					&all->p_philo[i]))
				exit_w_free("error: create thread\n", 1, all);
		}
		pthread_join(monitor, NULL);
		i = 0;
		while (i < all->p_params->n_of_philo)
			pthread_join(all->p_philo[i++].th_id, NULL);
	}
}
