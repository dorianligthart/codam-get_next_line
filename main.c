#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include "get_next_line.h"

#if 1
int main(int argc, char **argv)
{
	char	*str;
	// char 	*str2 = NULL;
	int		i = 0;
	if (argc != 3)
		return (0);
	int		fd = open(argv[1], O_RDONLY);
	int		fd2 = open(argv[2], O_RDONLY);
	while (fd >= 0 && fd2 >= 0 && i < 6)
	{
		str = get_next_line(fd);
		printf("GNL-RESULT:\n%i, %s\n", i, str);
		if (str)
			free(str);
		i++;
	}

	// {
	// 	str = get_next_line(fd);
	// 	printf("GNL-RESULT:\n%i, %s\n", i, str);
	// 	if (str)
	// 		free(str);
	// 	str2 = get_next_line(fd2);
	// 	printf("%i,\n%s‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n", i, str2);
	// 	if (str2)
	// 	{
	// 		printf("MAINabout to free\n");
	// 		free(str2);
	// 	}
	// 	i++;
	// 	printf("\n");
	// }
	return (0);
}
#endif