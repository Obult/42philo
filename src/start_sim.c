/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_sim.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: obult <obult@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 16:41:10 by obult         #+#    #+#                 */
/*   Updated: 2022/02/10 15:32:14 by obult         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_initer(t_general *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->times_eaten, NULL);
	while (i < (data->philocount + 9) / 10)
	{
		data->dead[i].check = 0;
		pthread_mutex_init(&data->dead[i].mut, NULL);
		i++;
	}
	i = 0;
	while (i < data->philocount)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	mutex_destroyer(t_general *data)
{
	int	i;

	i = 0;
	while (i < data->philocount)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	i = 0;
	while (i < (data->philocount + 9) / 10)
	{
		pthread_mutex_destroy(&data->dead[i].mut);
		i++;
	}
}

void	*start_sim(t_general *data)
{
	int	i;

	i = 0;
	mutex_initer(data);
	data->start_time = time_in_millis();
	while (i < data->philocount)
	{
		data->ph_info[i].last_eaten = data->start_time;
		pthread_create(&data->philos[i], NULL, iam_philo,
			(void *)&data->ph_info[i]);
		i++;
	}
	ph_holy_thread(data);
	while (i)
	{
		i--;
		pthread_join(data->philos[i], NULL);
	}
	mutex_destroyer(data);
	return (NULL);
}
