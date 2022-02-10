/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reaper.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: obult <obult@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 13:27:26 by obult         #+#    #+#                 */
/*   Updated: 2022/02/10 13:35:31 by obult         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	someonedied_function(t_general *data, int philo)
{
	int	i;

	i = 0;
	while (i < (data->philocount + 9) / 10)
	{
		pthread_mutex_lock(&data->dead[i].mut);
		data->dead[i].check = 1;
		i++;
	}
	printf("%i %i died\n", (int)elapsed_time(&data->ph_info[philo - 1]), philo);
	i = 0;
	while (i < (data->philocount + 9) / 10)
	{
		pthread_mutex_unlock(&data->dead[i].mut);
		i++;
	}
}

int	whale_loop(t_general *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->times_eaten);
	while (i < data->philocount)
	{
		if (data->eats != data->ph_info[i].times_eaten || data->eats == 0)
		{
			pthread_mutex_unlock(&data->times_eaten);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&data->times_eaten);
	return (1);
}

int	grim_reaper(t_general *data, int i)
{
	pthread_mutex_lock(&data->dead[i / 10].mut);
	if (time_in_millis() > data->ph_info[i].last_eaten
		+ data->time_to_die && data->ph_info[i].last_eaten != -1)
	{
		pthread_mutex_unlock(&data->dead[i / 10].mut);
		someonedied_function(data, i + 1);
		return (1);
	}
	else
		pthread_mutex_unlock(&data->dead[i / 10].mut);
	return (0);
}

void	ph_holy_thread(t_general *data)
{
	int	i;
	int	check;

	check = 0;
	while (1)
	{
		i = 0;
		while (i < data->philocount)
		{
			check = grim_reaper(data, i);
			if (check)
				break ;
			i++;
		}
		if (check || whale_loop(data))
			break ;
		usleep(600);
	}
}
