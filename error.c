/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaanit <rjaanit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:06:48 by rjaanit           #+#    #+#             */
/*   Updated: 2022/02/12 15:50:30 by rjaanit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_message(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

int	ft_error(char *str)
{
	perror(str);
	exit(1);
}
