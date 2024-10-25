/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:50:47 by tkirmizi          #+#    #+#             */
/*   Updated: 2024/10/25 14:51:54 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_all	*all;

	all = (t_all *)malloc(sizeof(t_all));
	if (!all)
		return (1);
	all->p_params = malloc(sizeof(t_params));
	if (!all->p_params)
	{
		free(all);
		return (1);
	}
	all->p_fork = NULL;
	if (ac == 5 || ac == 6)
	{
		handle_arguments(ac, av, all);
		philo_starter(all);
		thread_create(all);
		all_clean(all);
	}
	else
		exit_w_free("error: invalid arguments\n", 1, all);
	return (0);
}

void	handle_arguments(int ac, char **av, t_all *all)
{
	all->p_params->n_of_philo = ft_atoi(av[1]);
	all->p_params->t_die = ft_atoi(av[2]);
	all->p_params->t_eat = ft_atoi(av[3]);
	all->p_params->t_sleep = ft_atoi(av[4]);
	all->p_params->eat_done = 0;
	if (all->p_params->n_of_philo <= 0 || all->p_params->t_die <= 0
		|| all->p_params->t_eat <= 0 || all->p_params->t_sleep <= 0)
		exit_w_free("error: arguments value must more than 0\n", 1, all);
	if (all->p_params->t_die < 60 || all->p_params->t_eat < 60
		|| all->p_params->t_sleep < 60)
		exit_w_free("error: arguments value must more than 60\n", 1, all);
	if (all->p_params->n_of_philo > 200)
		exit_w_free("error: philosophers number should be less than 200",
			1, all);
	if (ac == 6)
	{
		all->p_params->max_eat = ft_atoi(av[5]);
		if (all->p_params->max_eat <= 0)
			exit_w_free("error: arguments value must more than 0\n", 1, all);
	}
	else
		all->p_params->max_eat = -1;
}
