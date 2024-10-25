/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deadext.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:50:53 by tkirmizi          #+#    #+#             */
/*   Updated: 2024/10/25 11:56:42 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_max_eat(t_all *all)
{
	int	i;
	int	total_meal;

	total_meal = 0;
	while (1)
	{
		i = 0;
		while (i < all->p_params->n_of_philo)
		{
			total_meal += all->p_philo[i].m_count;
			if (total_meal == all->p_params->max_eat
				* all->p_params->n_of_philo)
			{
				pthread_mutex_lock(&all->p_params->stop);
				all->p_params->eat_done = 1;
				pthread_mutex_lock(&all->p_params->stop);
			}
			i++;
		}
	}
}

int	meal_limit_reached(t_philo *philo)
{
	int	reached;

	reached = (philo->m_count >= philo->p_params->max_eat);
	if (philo->p_params->max_eat == -1)
		return (0);
	pthread_mutex_lock(&philo->p_params->stop);
	pthread_mutex_unlock(&philo->p_params->stop);
	return (reached);
}
