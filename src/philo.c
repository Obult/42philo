/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: obult <obult@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 11:39:47 by obult         #+#    #+#                 */
/*   Updated: 2022/02/09 20:23:22 by obult         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*iam_philo(void *arg)
{
	t_philo	*me;

	me = (t_philo *)arg;
	me->times_eaten = 0;
	if (me->id % 2 == 0)
		usleep(150);
	while (me->gen->eats == 0 || me->times_eaten < me->gen->eats)
	{
		if (ph_eat(me) == 1)
			break ;
		if (ph_sleep(me) == 1)
			break ;
		if (ph_think(me) == 1)
			break ;
		pthread_mutex_lock(&me->gen->times_eaten);
		me->times_eaten++;
		pthread_mutex_unlock(&me->gen->times_eaten);
		if (me->id == 1)
			usleep(500);
	}
	if (me->times_eaten == me->gen->eats && me->gen->eats != 0)
	{
		pthread_mutex_lock(&me->gen->dead[(me->id - 1) / 10].mut);
		me->last_eaten = -1;
		pthread_mutex_unlock(&me->gen->dead[(me->id - 1) / 10].mut);
	}
	return (NULL);
}
