/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: obult <obult@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 11:30:32 by obult         #+#    #+#                 */
/*   Updated: 2022/02/05 11:38:54 by obult         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_in_millis(void)
{
    struct timeval	tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}

long long	elapsed_time(t_philo *me)
{
	return (time_in_millis() - me->gen->start_time);
}

void	great_sleep(int	milli, t_philo *me)
{
	long long	time;

	time = (long long)milli + time_in_millis();
	if (me->last_eaten + (long long)me->gen->time_to_die < time)
		time = me->last_eaten + (long long)me->gen->time_to_die + 1;
	while (time  > time_in_millis())
	{
		usleep(200);
	}
}
