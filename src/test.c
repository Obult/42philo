/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: obult <obult@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/19 12:52:23 by obult         #+#    #+#                 */
/*   Updated: 2022/01/27 13:16:35 by obult         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

typedef struct s_multistruct
{
	int				num;
	pthread_mutex_t	mutex;
}					t_multistruct;

void	*start_routine(void *multi)
{
	t_multistruct	*data;

	data = (t_multistruct *)multi;
	usleep(15 * data->num);
	printf("%i\n", data->num);
	return (NULL);
}

int	main(void)
{
	t_multistruct	mult[4];
	int	i;
	pthread_t arr[4];
	pthread_mutex_t	*mutex;

	i = 0;
	mutex = 0;
	pthread_mutex_init(&mult[0].mutex, NULL);
	while (i < 4)
	{
		mult[i].num = i;
		mult[i].mutex = mult[0].mutex;
		pthread_create(&arr[i], NULL, start_routine, (void *)&(mult[i]));
		i++;
	}
	while (i)
	{
		i--;
		pthread_join(arr[i], NULL);
	}
	pthread_mutex_destroy(&mult[0].mutex);
}
