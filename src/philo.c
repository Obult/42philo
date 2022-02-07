/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: obult <obult@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 11:39:47 by obult         #+#    #+#                 */
/*   Updated: 2022/02/06 17:35:45 by obult         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	ph_death(t_philo *me)
// {
// 	printf("%i\n", pthread_mutex_lock(&me->gen->dead.mut));
// 	return (1);
// }

void	*iam_philo(void *arg)
{
	t_philo	*me;

	me = (t_philo *)arg;
	me->times_eaten = 0;
	if (me->id % 2 == 0)
		usleep(250);
	while (me->gen->eats == 0 || me->times_eaten < me->gen->eats)
	{
		if (ph_eat(me) == 1)
			break ;
		if (ph_sleep(me) == 1)
			break ;
		if (ph_think(me) == 1)
			break ;
		me->times_eaten++;
	}
	if (me->times_eaten == me->gen->eats && me->times_eaten != 0)
		me->last_eaten = -1;
	return (NULL);
}
