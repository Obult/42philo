/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: obult <obult@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 13:32:22 by obult         #+#    #+#                 */
/*   Updated: 2022/02/09 18:36:44 by obult         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     main(int argc, char **argv)
{
	t_general   data;

	if (argc < 5 || argc > 6)
		return (1);
	if (argc == 6 && argv[5][0] == '0')
		return (2);
	if (parse_input(&data, argv, argc))
		return (3);
	if (ph_initer(&data) == 1)		// first malloc
		return (4);
	start_sim(&data);
	if (data.forks)
		free(data.forks);
	if (data.philos)
		free(data.philos);
	if (data.ph_info)
		free(data.ph_info);
	if (data.dead)
		free(data.dead);
	return (0);
}
