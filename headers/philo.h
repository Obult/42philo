/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: obult <obult@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/19 14:18:48 by obult         #+#    #+#                 */
/*   Updated: 2022/02/05 16:12:24 by obult         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo t_philo;

typedef struct s_dead
{
	pthread_mutex_t	mut;
	int				check;
}					t_dead;

typedef struct s_general
{
	int				errornum;
	int				philocount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eats;

	pthread_mutex_t	*forks;
	pthread_t		*philos;
	t_philo			*ph_info;
	t_dead			*dead;
	long long		start_time;
}					t_general;

typedef struct s_philo
{
	int			id;
	int			times_eaten;
	t_general	*gen;
	long long	last_eaten;
}				t_philo;

int	ph_atoi(const char *nptr, int *error);
int	parse_input(t_general *data, char **argv, int argc);

int	ph_initer(t_general *data);
int     parse_input(t_general *data, char **argv, int argc);
void	*start_sim(t_general *data);
void	*iam_philo(void *arg);

// void	great_sleep(int	mili);
void	great_sleep(int	milli, t_philo *me);
long long	elapsed_time(t_philo *me);
long long	time_in_millis(void);

int	ph_death(t_philo *me);
int	ph_print(t_philo *me, char *msg);
int	ph_eat(t_philo *me);
int	ph_sleep(t_philo *me);
int	ph_think(t_philo *me);

int	grab_fork(t_philo *me, int offset);

#endif