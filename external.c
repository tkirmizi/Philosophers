/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:46:42 by tkirmizi          #+#    #+#             */
/*   Updated: 2024/10/25 11:57:07 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->p_params->dead_mutex);
	if (!philo->p_params->dead)
	{
		pthread_mutex_lock(&philo->p_params->print);
		printf("%u %d %s\n",
			get_current_time() - philo->p_params->start_time,
			philo->id, status);
		pthread_mutex_unlock(&philo->p_params->print);
	}
	pthread_mutex_unlock(&philo->p_params->dead_mutex);
}

void	ft_sleep(unsigned int ms)
{
	unsigned int	start;

	start = get_current_time();
	while ((get_current_time() - start) < ms)
	{
		usleep(10);
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	indc;

	i = 0;
	result = 0;
	indc = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			indc *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	return (indc * result);
}
