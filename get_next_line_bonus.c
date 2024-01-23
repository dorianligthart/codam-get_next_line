/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 22:31:52 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/23 12:03:12 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h> 	//ft_malloc, free
#include <unistd.h>		//read

static char	*splitnl(char **prefix, int i, char *result, char *tmp)
{
	int	suffix_len;

	suffix_len = 0;
	while (*prefix && (*prefix)[i + suffix_len])
		suffix_len++;
	if (suffix_len)
	{
		tmp = malloc(suffix_len + 1);
		if (!tmp)
			return (free(*prefix), *prefix = NULL, NULL);
		tmp[suffix_len] = '\0';
		while (suffix_len--)
			tmp[suffix_len] = (*prefix)[i + suffix_len];
	}
	result = malloc(i + 1);
	if (!result)
		return (free(tmp), free(*prefix), *prefix = NULL, NULL);
	result[i] = '\0';
	while (i--)
		result[i] = (*prefix)[i];
	free(*prefix);
	*prefix = tmp;
	return (result);
}

//	returns the next line from file descriptor `fd'. 
//	sizeof(char *) = 8, 8 * 2048 = 16384 bytes on static memory.
//	malloc(BUFFER_SIZE*n^2), where n is the amount of recursion it has to do
//		resulted from how big the line is, compared to how small BUFFER_SIZE is.
char	*get_next_line(int fd)
{
	char		*tmp;
	static char	*prefix[2048];
	ssize_t		read_return;
	int			i;

	i = 0;
	while (prefix[fd] && prefix[fd][i])
		if (prefix[fd][i++] == '\n')
			return (splitnl(&(prefix[fd]), i, NULL, NULL));
	tmp = malloc(i + BUFFER_SIZE + 1);
	if (!tmp)
		return (free(prefix[fd]), prefix[fd] = NULL, NULL);
	read_return = read(fd, tmp + i, BUFFER_SIZE);
	if (read_return < 0)
		return (free(tmp), free(prefix[fd]), prefix[fd] = NULL, NULL);
	tmp[i + read_return] = '\0';
	if (read_return == 0 && (!prefix[fd] || !*prefix[fd]))
		return (prefix[fd] = NULL, free(tmp), NULL);
	while (i--)
		tmp[i] = prefix[fd][i];
	free(prefix[fd]);
	prefix[fd] = tmp;
	if (read_return == 0)
		return (prefix[fd] = NULL, tmp);
	return (get_next_line(fd));
}
