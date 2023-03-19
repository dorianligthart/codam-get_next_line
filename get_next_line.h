/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dligthar <dligthar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 16:31:20 by dligthar      #+#    #+#                 */
/*   Updated: 2023/03/18 23:59:40 by dligthar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef		GET_NEXT_LINE_H
# define	GET_NEXT_LINE_H

//needed libraries:
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

//default BUFF
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

//libft function:
char	*ft_substr(char const *s1, unsigned int start, size_t len);

//-------------------------------------------//
// Get Next Line Functions with description: //
//-------------------------------------------//
		//A function that returns length of s or length until c is found.
size_t	ft_strlen_chr(char *s, char c);
		//Splits src into "{return} and src" at first occurence of c in src.
char	*gnl_shift(char *src, char **src_loc, char c);
		//returns(prefix + read(fd, buffer, BUFFERSIZE)); frees prefix;
char	*gnl_buff_append_read(char *s1, int fd, int *eof, char c);
		//returns the next line read from file descriptor fd.
char	*get_next_line(int fd);
#endif