#include "cub3d.h"


void check_file_exists(char *argv, int *fd)
{
    *fd = open(argv, O_RDONLY);
    if (*fd == -1)
    {
        ft_put_error("Error: File not found");
        exit(EXIT_FAILURE);
    }
}



void	ft_check_argc_and_name(int argc, char *argv[])
{
	size_t	i;
	char	*c;

	if (argc != 2)
	{
		ft_put_error("Error: Wrong argc quantity");
		exit(EXIT_FAILURE);
	}
	i = ft_strlen(argv[1]);
	c = &argv[1][i - 4];
	if (ft_strncmp(c, ".cub", 4))
	{
		ft_put_error("Error: Wrong filename");
		exit(EXIT_FAILURE);
	}
	return ;
}