/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: obult <obult@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 16:38:20 by obult         #+#    #+#                 */
/*   Updated: 2022/02/09 15:53:13 by obult         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	grab_fork(t_philo *me, int offset)
{
	int	fork_id;
	int	dead;

	fork_id = (me->id + offset) % me->gen->philocount;
	pthread_mutex_lock(&me->gen->forks[fork_id]);
	dead = ph_print(me, "has taken a fork");
	if (dead)
		pthread_mutex_unlock(&me->gen->forks[fork_id]);
	return (dead);
}

int	grab_forks_plural(t_philo *me)
{
	if (me->id % 2 == 1)
	{
		if (grab_fork(me, -1))
			return(1);
		if (me->gen->philocount == 1)
		{
			great_sleep(me->gen->time_to_die + 10);
			printf("fork dead\n");
			pthread_mutex_unlock(&me->gen->forks[me->id % me->gen->philocount]);
			return (1);
		}
		if (grab_fork(me, 0))
		{
			pthread_mutex_unlock(&me->gen->forks[me->id - 1]);
			return (1);
		}
	}
	else
	{
		if (grab_fork(me, 0))
			return(1);
		if (grab_fork(me, -1))
		{
			pthread_mutex_unlock(&me->gen->forks[me->id % me->gen->philocount]);
			return (1);
		}
	}
	return (0);
}
