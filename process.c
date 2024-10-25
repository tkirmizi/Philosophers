/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:51:16 by tkirmizi          #+#    #+#             */
/*   Updated: 2024/10/25 15:01:59 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_philo(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(&philo->p_params->dead_mutex);
	is_dead = philo->p_params->dead;
	pthread_mutex_unlock(&philo->p_params->dead_mutex);
	if (philo->p_params->max_eat != -1 && (is_dead
			|| philo->m_count >= philo->p_params->max_eat))
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(philo->r_fork->mutex));
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->l_fork->mutex));
	}
	else
	{
		pthread_mutex_lock(&(philo->l_fork->mutex));
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->r_fork->mutex));
	}
	eat_philo_2(philo, is_dead);
}

void	eat_philo_2(t_philo *philo, int is_dead)
{
	unsigned int	start;
	int				i;

	i = 0;
	start = get_current_time();
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->eat_lock);
	philo->last_meal = start;
	if (!is_dead)
	{
		print_status(philo, "is eating");
		while (i < philo->p_params->t_eat && !is_dead)
		{
			usleep(10);
			pthread_mutex_lock(&philo->p_params->dead_mutex);
			is_dead = philo->p_params->dead;
			pthread_mutex_unlock(&philo->p_params->dead_mutex);
			i = get_current_time() - start;
		}
	}
	philo->m_count++;
	pthread_mutex_unlock(&philo->eat_lock);
	pthread_mutex_unlock(&(philo->l_fork->mutex));
	pthread_mutex_unlock(&(philo->r_fork->mutex));
}

void	sleep_philo(t_philo *philo)
{
	if (!philo->p_params->dead)
	{
		print_status(philo, "is sleeping");
		ft_sleep(philo->p_params->t_sleep);
	}
}

void	think_philo(t_philo *philo)
{
	if (!philo->p_params->dead)
	{
		print_status(philo, "is thinking");
		ft_sleep(1);
	}
}
