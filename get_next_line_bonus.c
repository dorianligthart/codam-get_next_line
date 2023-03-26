/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dligthar <dligthar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 16:31:20 by dligthar      #+#    #+#                 */
/*   Updated: 2023/03/26 14:38:35 by dligthar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen_chr(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		i++;
	return (i);
}

char	*gnl_splitnl(char **arr, char c)
{
	char	*ret;
	char	*tmp_arr;
	size_t	split;

	if (!*arr || !*arr[0])
		return (NULL);
	split = ft_strlen_chr(*arr, c);
	ret = ft_substr(*arr, 0, split);
	if (!ret)
		return (NULL);
	tmp_arr = ft_strdup(*arr + split);
	free(*arr);
	*arr = tmp_arr;
	return (ret);
}

char	*gnl_free_return_null(char *str)
{
	if (str || str[0])
		free(str);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*arr[4096] = {NULL}; //char pointer!!
	char		*buf;
	char		*tmp;
	char		c;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buf = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buf)
		return (NULL);
	c = '\n';
	bytes = 42;
	while (0 < bytes && !ft_strchr(arr[fd], c))
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
			return (gnl_free_return_null(buf));
		buf[bytes] = '\0';
		tmp = ft_strjoin(arr[fd], buf);
		free(arr[fd]);
		arr[fd] = tmp;
	}
	free(buf);
	return (gnl_splitnl(&arr[fd], c));
}