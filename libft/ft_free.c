/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:38:53 by suhwpark          #+#    #+#             */
/*   Updated: 2023/02/15 15:53:55 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(char **p)
{
	int	i;

	i = -1;
	while (p[++i])
		free(p[i]);
	free(p);
}
