/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ph_input.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: obult <obult@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 16:57:13 by obult         #+#    #+#                 */
/*   Updated: 2022/02/05 16:48:13 by obult         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     parse_input(t_general *data, char **argv, int argc)
{
    int error;

    error = 0;
    data->philocount = ph_atoi(argv[1], &error);
    data->time_to_die = ph_atoi(argv[2], &error);
    data->time_to_eat = ph_atoi(argv[3], &error);
    data->time_to_sleep = ph_atoi(argv[4], &error);
    if (argc == 6)
        data->eats = ph_atoi(argv[5], &error);
    if (data->philocount < 0 || data->time_to_die < 0 || data->time_to_eat < 0
        || data->time_to_sleep < 0)
        return (1);
    if (argc == 6 && data->eats < 0)
        return (1);
    return (error);
}

static int	ph_asign_values(t_general *data)
{
	int	i;

	i = 0;
	while (i < data->philocount)
	{
		data->ph_info[i].id = i + 1;
		data->ph_info[i].gen = data;
		i++;
	}
	return (0);
}

int	ph_initer(t_general *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philocount);
	if (!data->forks)
		return (1);
	data->philos = malloc(sizeof(pthread_t) * data->philocount);
	if (!data->philos)
	{
		free(data->forks);
		return (1);
	}
	data->ph_info = malloc(sizeof(t_philo) * data->philocount);
	if (!data->ph_info)
	{
		free(data->forks);
		free(data->philos);
		return (1);
	}
	data->dead = malloc((data->philocount + 9) / 10 * sizeof(t_dead));
	if (!data->dead)
	{
		free(data->forks);
		free(data->philos);
		free(data->ph_info);
		return (1);	
	}
	return (ph_asign_values(data));
}
