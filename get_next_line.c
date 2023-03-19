/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dligthar <dligthar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 16:31:20 by dligthar      #+#    #+#                 */
/*   Updated: 2023/03/18 23:59:46 by dligthar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "get_next_line.h"

char	*gnl_shift(char *src, char **src_loc, char c)
{
	char	*result;
	char	*tmp;
	int		splitval;
	int		i;

	splitval = ft_strlen_chr(src, c);
	result = malloc(splitval * sizeof(char) + 1);
	if (!result)
		return (NULL);
	i = splitval;
	result[i] = '\0';
	while (i--)
		result[i] = src[i]; // first half of str.
	i = ft_strlen_chr(src, '\0'); //i becomes whole len.
	tmp = malloc((i - splitval) * sizeof(char) + 1);
	if (!tmp)
		return (NULL);
	tmp[i - splitval] = '\0';
	while (-splitval + i--)
		tmp[i] = src[-splitval + i];
	free(src);
	src_loc = &tmp;
	printf("shift REACHED with %s\n", *src_loc);
	return (result);
}

char	*gnl_buff_append_read(char *s1, int fd, int *eof, char c)
{
	int		len;
	int		lencopy;
	char	*result;

	len = ft_strlen_chr(s1, c);
	result = (char *)malloc((len + BUFFER_SIZE + 1) * sizeof(char));
	if (!result)
		return (NULL);
	lencopy = len;
	while (lencopy--)
		result[lencopy] = s1[lencopy];
	if (s1 && !eof)
		free(s1);
	lencopy = read(fd, (char *)(result + len), BUFFER_SIZE);
	if (lencopy < BUFFER_SIZE)
		*eof = 1;
	if (lencopy < 0)
	{
		free(result);
		return (NULL);
	}
	result[len + lencopy] = '\0';
	return (result);
}

char	*get_next_line(int fd)
{
	static char *arr[4096] = {NULL};
	int			eof;
	char		c;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	c = '\n';
	eof = 0;
	while (!arr[fd] || arr[fd][ft_strlen_chr(arr[fd], c)] != c)
	{
		arr[fd] = gnl_buff_append_read(arr[fd], fd, &eof, c);
		printf("REACHED with %s\n", arr[fd]);
		if (arr[fd] && eof)
		{
			return (arr[fd]);
		}
		if (!arr[fd] || eof)
			return (NULL);
	}
	return (gnl_shift(arr[fd], &arr[fd], c));
}
