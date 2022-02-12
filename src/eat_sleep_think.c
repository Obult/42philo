/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: obult <obult@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 16:02:29 by obult         #+#    #+#                 */
/*   Updated: 2022/02/12 13:12:08 by obult         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_death(t_philo *me)
{
	int	mut_id;

	mut_id = (me->id - 1) / 10;
	pthread_mutex_lock(&me->gen->dead[mut_id].mut);
	if (me->gen->dead[mut_id].check != 0)
	{
		pthread_mutex_unlock(&me->gen->dead[mut_id].mut);
		return (1);
	}
	if (time_in_millis() > me->last_eaten + me->gen->time_to_die)
	{
		pthread_mutex_unlock(&me->gen->dead[mut_id].mut);
		return (1);
	}
	return (0);
}

int	ph_print(t_philo *me, char *msg)
{
	if (ph_death(me) == 0)
	{
		printf("time: %i, philo: %i %s\n", (int)elapsed_time(me), me->id, msg);
		pthread_mutex_unlock(&me->gen->dead[(me->id - 1) / 10].mut);
		return (0);
	}
	return (1);
}

int	ph_eat(t_philo *me)
{
	if (grab_forks_plural(me))
		return (1);
	if (ph_print(me, "is eating") == 0)
	{
		pthread_mutex_lock(&me->gen->dead[(me->id - 1) / 10].mut);
		me->last_eaten = time_in_millis();
		pthread_mutex_unlock(&me->gen->dead[(me->id - 1) / 10].mut);
		great_sleep(me->gen->time_to_eat);
		pthread_mutex_unlock(&me->gen->forks[me->id - 1]);
		pthread_mutex_unlock(&me->gen->forks[me->id % me->gen->philocount]);
		return (0);
	}
	return (1);
}

int	ph_sleep(t_philo *me)
{
	if (ph_print(me, "is sleeping") == 0)
	{
		great_sleep(me->gen->time_to_sleep);
		return (0);
	}
	return (1);
}

int	ph_think(t_philo *me)
{
	return (ph_print(me, "is thinking"));
}
