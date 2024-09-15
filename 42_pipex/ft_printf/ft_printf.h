/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:45:54 by svalchuk          #+#    #+#             */
/*   Updated: 2024/05/07 21:50:55 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include "libft/libft.h"
# include <stdarg.h>

int		ft_printf(const char *input, ...);
char	*get_next_line(int fd);
size_t	ft_strlen_gnl(char const *str);
char	*ft_strchr_gnl(const char *s, int c);
char	*ft_substr_gnl(const char *s, unsigned int start, size_t len);
char	*ft_strjoin_gnl(char const *s1, char const *s2);

#endif