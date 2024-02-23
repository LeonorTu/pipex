/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:40:08 by jtu               #+#    #+#             */
/*   Updated: 2023/11/14 18:13:26 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The isdigit() function tests for a decimal digit character.
 */
int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
