/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 00:33:32 by ivalimak          #+#    #+#             */
/*   Updated: 2024/11/08 16:02:13 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define _read	(rv = read(0, buf, 8))

static inline void	__exit(void);

struct termios	old;
struct termios	new;

int32_t	main(void)
{

	size_t	i;
	ssize_t	rv;
	uint8_t	buf[65];

	atexit(__exit);
	tcgetattr(0, &old);
	new = old;
	new.c_iflag &= ~(ICRNL | IXON);
	new.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	tcsetattr(0, TCSANOW, &new);
	memset(buf, 0, 65);
	for (_read; rv > 0; _read) {
		if (strncmp((const char *)buf, "\x4", 2) == 0)
			break ;
		for (i = 0; buf[i]; i++) {
			if (isprint(buf[i]))
				putchar(buf[i]);
			else
				printf("^%c", buf[i] + '@');
		}
		putchar('\n');
		memset(buf, 0, 64);
	}
	return 0;
}

static inline void	__exit(void)
{
	tcsetattr(0, TCSANOW, &old);
}
