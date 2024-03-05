/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:56:21 by jtu               #+#    #+#             */
/*   Updated: 2023/11/22 15:34:29 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"

int	main(void)
{
	// int c1 = ft_printf("%c\n", '0');
	// int c2 = printf("%c\n", '0');
	// printf("ft_printf: %d\n", c1);
	// printf("printf: %d\n", c2);

	// int c3 = ft_printf(" %d\n", -11);
	// int c4 = printf(" %d\n", -11);
	// printf("ft_printf: %d\n", c3);
	// printf("printf: %d\n", c4);

	// int c5 = ft_printf("%p\n", (void*)1);
	// int c6 = printf("%p\n", (void*)1);
	// printf("ft_printf: %d\n", c5);
	// printf("printf: %d\n", c6);

	// int c7 = ft_printf("%x\n", LONG_MIN);
	// int c8 = printf("%x\n", LONG_MIN);
	// printf("ft_printf: %d\n", c7);
	// printf("printf: %d\n", c8);

	// int c9 = ft_printf("%u\n", -10);
	// int c10 = printf("%u\n", -10);
	// printf("ft_printf: %d\n", c9);
	// printf("printf: %d\n", c10);

	// int c11 = ft_printf("%p %p \n", LONG_MIN, LONG_MAX);
	// int c12 = printf("%p %p \n", LONG_MIN, LONG_MAX);
	// printf("ft_printf: %d\n", c11);
	// printf("printf: %d\n", c12);

	// int c13 = printf(" NULL %s NULL ", NULL);
	// printf("printf: %d\n", c13);
	// int c14 = ft_printf(" NULL %s NULL ", NULL);
	// printf("printf: %d\n", c14);

	int c15 = printf("\001\002\007\v\010\f\r\n");
	printf("printf: %d\n", c15);
	int c16 = ft_printf("\001\002\007\v\010\f\r\n");
	printf("ft_printf: %d\n", c16);

}
