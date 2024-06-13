/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 00:33:32 by ivalimak          #+#    #+#             */
/*   Updated: 2024/06/14 00:54:07 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

static inline void	__exit(void);

struct termios	osettings;
struct termios	nsettings;

int32_t	main(void)
{
	uint64_t	key;

	atexit(__exit);
	tcgetattr(0, &osettings);
	nsettings = osettings;
	nsettings.c_iflag &= ~(ICRNL | IXON);
	nsettings.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	tcsetattr(0, TCSANOW, &nsettings);
	if (read(0, &key, sizeof(key)) == -1)
	{
		perror("keycoder");
		return (1);
	}
	while (key != 4)
	{
		printf("%lX", key);
		if (key >= ' ' && key <= '~')
			printf(" '%c'", (char)key);
		printf("\n");
		key = 0;
		if (read(0, &key, sizeof(key)) == -1)
		{
			perror("keycoder");
			return (1);
		}
	}
	printf("%lu", key);
	if (key >= ' ' && key <= '~')
		printf(" '%c'", (char)key);
	printf("\n");
	return (0);
}

static inline void	__exit(void)
{
	tcsetattr(0, TCSANOW, &osettings);
}
