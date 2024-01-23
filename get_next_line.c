/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 22:31:52 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/23 12:03:08 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// //debug needed by main():
// #define BUFFER_SIZE 3
// #include <fcntl.h> //open()
// #include <stdio.h> //printf()

#include "get_next_line.h"
#include <stdlib.h> 	//malloc(), free()
#include <unistd.h>		//read(), main()->close()

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
//	malloc(BUFFER_SIZE*n^2), where n is the amount of recursion it has to do
//		resulted from how big the line is, compared to how small BUFFER_SIZE is.
char	*get_next_line(int fd)
{
	char		*tmp;
	static char	*prefix;
	ssize_t		read_return;
	int			i;

	i = 0;
	while (prefix && prefix[i])
		if (prefix[i++] == '\n')
			return (splitnl(&prefix, i, NULL, NULL));
	tmp = malloc(i + BUFFER_SIZE + 1);
	if (!tmp)
		return (free(prefix), prefix = NULL, NULL);
	read_return = read(fd, tmp + i, BUFFER_SIZE);
	if (read_return < 0)
		return (free(tmp), free(prefix), prefix = NULL, NULL);
	tmp[i + read_return] = '\0';
	if (read_return == 0 && (!prefix || !*prefix))
		return (prefix = NULL, free(tmp), NULL);
	while (i--)
		tmp[i] = prefix[i];
	free(prefix);
	prefix = tmp;
	if (read_return == 0)
		return (prefix = NULL, tmp);
	return (get_next_line(fd));
}

////////////////////////////////////////////////////////////////////////////////
//	GET_NEXT_LINE, read() RETURN HANDLING:
//
//  Note that pre always gets copied to tmp.
//
//	Possibilities:		  		Case:	 	do:							return:
//	read_return < 0 && pre;		error: 		pre=NULL, free(pre + tmp),	NULL;
//	read_return < 0 && !pre;	error: 		pre=NULL, free(tmp), 		NULL;
//	read_return == 0 && pre;	EOF: 		pre=NULL, free(pre), 		tmp;
//	read_return == 0 && !pre;	past EOF: 	pre=NULL, free(tmp),		NULL;
////////////////////////////////////////////////////////////////////////////////

// void	*ft_malloc(size_t size)
// {
// 	static int i = 0;

// 	if (i > 3)
// 		return (NULL);
// 	i++;
// 	return (malloc(size));
// }

// int main(void)
// {
// 	int		fd = open("test.txt", O_RDONLY);
// 	// int		fd = 3;
// 	// int		fd = 1;
// 	if (fd < 0)
// 		return (1);
// 	char	*hold = NULL;

// 	int i = 0
// 	hold = get_next_line(fd);
// 	while (hold || i < 10000)
// 	{
// 		printf("%s", hold);
// 		free(hold);
// 	 	hold = get_next_line(fd);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }
