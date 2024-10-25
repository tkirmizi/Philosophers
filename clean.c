/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:48:42 by tkirmizi          #+#    #+#             */
/*   Updated: 2024/10/25 11:54:57 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	all_clean(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->p_params->n_of_philo)
	{
		pthread_mutex_destroy(&(all->p_params->p_forks[i].mutex));
		pthread_mutex_destroy(&all->p_params->print);
		pthread_mutex_destroy(&all->p_params->stop);
		pthread_mutex_destroy(&all->p_params->dead_mutex);
		free(all->p_params->p_forks);
		free(all->p_philo);
		free(all->p_params);
		free(all);
	}
}

void	exit_w_free(char *str, int i, t_all *all)
{
	if (all->p_philo)
		free(all->p_philo);
	if (all->p_fork)
		free(all->p_fork);
	perror(str);
	exit(i);
}

unsigned int	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
