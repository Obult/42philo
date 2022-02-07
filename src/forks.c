/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: obult <obult@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 16:38:20 by obult         #+#    #+#                 */
/*   Updated: 2022/02/04 18:08:45 by obult         ########   odam.nl         */
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