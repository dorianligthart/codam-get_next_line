/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dligthar <dligthar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 16:31:20 by dligthar      #+#    #+#                 */
/*   Updated: 2023/03/18 23:59:50 by dligthar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_chr(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s && s[i] && s[i] != c)
		i++;
	return (i);
}

char	*ft_substr(char const *s1, unsigned int start, size_t len)
{
	size_t	len_s1;
	char	*s2;

	if (len == 0 || !s1 || !s1[0])
		return (NULL);
	len_s1 = 0;
	while (s1[len_s1])
		len_s1++;
	if (start >= len_s1)
		return (NULL);
	if (start + len > len_s1)
		len = len_s1 - start;
	s2 = (char *)malloc((len + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	s2[len] = '\0';
	while (len--)
		s2[len] = s1[start + len];
	return (s2);
}


//tmp:
// char	*gnl_read(int fd, char **prefix, int *eof) //WORKING CORRECTLY AND AS INTENDED!!
// {
// 	char	*result;
// 	int		prefixlen;
// 	int		readlen;

// 	printf("gnl_read\n");
// 	if (*eof)
// 	{
// 		printf("	accidental eof\n");
// 		return (NULL); //copy whole string.
// 	}
// 	prefixlen = ft_strlen_chr(prefix[fd], '\0');
// 	printf("	prefix:\"%s\" with len:%d about to free\n", prefix[fd], prefixlen);
// 	printf("	prefixlen = %d\n", prefixlen);
// 	result = malloc((prefixlen + BUFFER_SIZE) * sizeof(char) + 1);
// 	if (!result)
// 		return (NULL);
// 	readlen = prefixlen;
// 	while (readlen--)
// 		result[readlen] = prefix[fd][readlen];
// 	if (prefixlen > 0)
// 	{
// 		printf("	prefix free reached\n");
// 		free(*prefix);
// 	}
// 	readlen = read(fd, result, BUFFER_SIZE);
// 	if (readlen < 0)
// 	{
// 		free(result);
// 		return (NULL);
// 	}
// 	if (readlen < BUFFER_SIZE)
// 		*eof = 1;
// 	result[prefixlen + readlen] = '\0';
// 	printf("	read REACHED:\n		result=%s!\n		and len=%d,eof=%d\n", result, prefixlen + readlen, *eof);
// 	return (result);
// }