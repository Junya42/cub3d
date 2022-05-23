/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 00:37:35 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/03 16:50:53 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int	ft_putchar(char c, int fd);
int	ft_putstr(char *str, int fd);
int	ft_putnbrsize(int n, int fd);
int	ft_putunbrsize(unsigned int n, int fd);
int	ft_returnputx(unsigned int n, char x, int fd);
int	ft_returnaddress(unsigned long int n, char x, int fd);
int	ft_printf(const char *format, ...);

#endif
