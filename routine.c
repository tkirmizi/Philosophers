/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:47:11 by tkirmizi          #+#    #+#             */
/*   Updated: 2024/10/25 14:27:33 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_for_alone(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = philo->p_params->start_time;
	printf("%u 1 has taken a fork\n", get_current_time()
		- philo->p_params->start_time);
	ft_sleep(philo->p_params->t_die);
	printf("%u 1 died\n", get_current_time() - philo->last_meal);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	int			is_dead;

	philo = (t_philo *)arg;
	philo->last_meal = get_current_time();
	if (philo->id % 2 == 0)
		ft_sleep(philo->p_params->t_eat / 2);
	while (1)
	{
		pthread_mutex_lock(&philo->p_params->dead_mutex);
		is_dead = philo->p_params->dead;
		pthread_mutex_unlock(&philo->p_params->dead_mutex);
		if (is_dead)
			break ;
		eat_philo(philo);
		if (is_dead)
			break ;
		sleep_philo(philo);
		if (is_dead)
			break ;
		think_philo(philo);
		if (is_dead)
			break ;
	}
	return (NULL);
}
