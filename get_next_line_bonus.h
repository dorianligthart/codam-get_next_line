/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dligthar <dligthar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 18:22:24 by dligthar      #+#    #+#                 */
/*   Updated: 2023/03/26 15:03:30 by dligthar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

//needed libraries:
# include <stddef.h>

//default BUFFER_SIZE
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

//libft functions:
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);

//returns strlen(s) but until c is found, including c.
size_t	ft_strlen_chr(const char *s, char c);
//Splits src into "{return str} and src" at first occurence of c in src.
char	*gnl_splitnl(char **src, char c);
//If str || str[0], frees str and returns NULL.
char	*gnl_free_return_null(char *str);
//returns the next line read from file descriptor fd.
char	*get_next_line(int fd);
#endif
