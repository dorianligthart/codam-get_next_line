/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dligthar <dligthar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 14:48:21 by dligthar      #+#    #+#                 */
/*   Updated: 2023/03/26 14:40:34 by dligthar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BONUS
# define BONUS 1
#endif
#if BONUS
#include "get_next_line_bonus.h"
#endif
#if !BONUS
#include "get_next_line.h"
#endif
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	// printf("strncmp\n");
	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	while (i < n)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

void	printonerror(char *expected, char *result)
{
	printf("\n	\033[0;31mexpected: \"%s\", but got \"%s\"\n\033[0m", expected, result);
}

void	printtest(int fd, char *comp, char *name)
{
	char *str;
	
	str = get_next_line(fd);
	printf("%s:", name);
	if (ft_strncmp(str, comp, 10000))
		printonerror(comp, str);
	else
		printf("	\033[0;32m[OK]\n\033[0m");
	if (str && str[0])
		free(str);
}

void	leakchk(void)
{
	system("leaks -q a.out");
}

int main(void)
{
	atexit(leakchk);

	int		fd0 = open("test_files/empty", O_RDONLY);
	int		fd1 = open("test_files/1char", O_RDONLY);
	int		fd2 = open("test_files/1nl", O_RDONLY);
	int		fd3 = open("test_files/endonnl", O_RDONLY);
	int		fd4 = open("test_files/endoneof", O_RDONLY);

	if (fd0 && fd1 && fd2 && fd3 && fd4)
	{
		//man: printtest(fd, EXPECTED, NAME_OF_FILE);
		printf("\033[0;36m\nBUFFERSIZE: %d\n\033[0m", BUFFER_SIZE);
		printf("\033[0;33mONE line testfiles:\n\033[0m");
			printtest(fd0, NULL, "empty		");
			printtest(fd1, "d", "1char		");
			printtest(fd2, "\n", "1nl		");
			printtest(fd3, "abc\n", "end_on_nl	");
			printtest(fd4, "abc\n", "end_on_eof	");

		printf("\033[0;33mTWO line testfiles:\n\033[0m");
			printtest(fd3, "123\n", "end_on_nl	");
			printtest(fd4, "123", "end_on_eof	");
			printtest(fd2, "\n", "1nl		");
			printtest(fd2, "\n", "1nl		");
			printtest(fd2, "\n", "1nl		");

		printf("\033[0;33mthird line final test (should be all NULL):\n\033[0m");
			printtest(fd0, NULL, "empty		");
			printtest(fd1, NULL, "1char		");
			printtest(fd2, NULL, "1nl		");
			printtest(fd3, NULL, "end_on_nl	");
			printtest(fd4, NULL, "end_on_eof	");
			printtest(fd3, NULL, "end_on_nl	");
			printtest(fd4, NULL, "end_on_eof	");
	}
	printf ("[end test]\n\n");
	close(fd0);
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
	return (0);
}
//normal:
//	clang -Wall -Werror -Wextra get_next_line_utils.c get_next_line.h get_next_line.c main.c
//	clang -fsanitize=address get_next_line_utils.c get_next_line.h get_next_line.c

//bonus:
//	clang -Wall -Werror -Wextra get_next_line_utils_bonus.c get_next_line_bonus.h get_next_line_bonus.c main.c
//	clang -Wall -Werror -Wextra -fsanitize=address get_next_line_utils_bonus.c get_next_line_bonus.h get_next_line_bonus.c main.c