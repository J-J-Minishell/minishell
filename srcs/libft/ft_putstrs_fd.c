#include "libft.h"

int	ft_putstrs_fd(char *before, char *str, char *after, int fd)
{
	if (before)
		write(fd, before, ft_strlen(before));
	if (str)
		write(fd, str, ft_strlen(str));
	if (after)
		write(fd, after, ft_strlen(after));
	return (1);
}
