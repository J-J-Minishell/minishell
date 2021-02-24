#include "libft.h"

void	*ft_free_ptr(void *ptr)
{
	free(ptr);
	return (NULL);
}
