#include "cub3d.h"

#include <string.h>


int main(int argc, char **argv) 
{
    struct game Game;
   ft_check_argc_and_name(argc, argv);
    ft_get_map(argv[1], &Game); 
    printf("\n[%s]\n", Game.map[4]);
   // exit(1);
    ft_check_map(&Game); 
  printf("MAP IS VALID\n");
  //ft_print_map(&Game);

  free_map(&Game);
  printf("F [%s]\n", Game.attr.f);
printf("C [%s]\n", Game.attr.c);
  free_attributes(&Game);

  return 0;
}

/////////////////////////////////


void free_map(struct game *Game)
{
    if (!Game->map)
        return ;
    if (Game->map != NULL)
    {
        for (int i = 0; i < Game->height; i++)
            free(Game->map[i]);
        free(Game->map);
    }
}



void ft_get_map(char *argv, struct game *Game)
{
    init_attributes(Game);
    printf("Getting map\n");
    int fd;
    check_file_exists(argv, &fd); // Check if it's a file not a directory

    // Crop Map
    int map_start = 0;
    char *line = NULL;

    while ((line = get_next_line(fd)))
    {
        if (is_valid_attr(Game, line))
        {
            map_start++;
            printf("\n[%d]\n", check_attr_count(Game));
            if (check_attr_count(Game))
            {
                free(line);
                break;
            }
            free(line);
            continue;
        }
        free(line);
    }

    printf("MAP STARTS FROM [%d] line\n", map_start); 
    check_attr_path(Game);

    printf("NO [%s]\n", Game->attr.no);
    printf("SO [%s]\n", Game->attr.so);
    printf("WE [%s]\n", Game->attr.we);
    printf("EA [%s]\n", Game->attr.ea);
    printf("F [%s]\n", Game->attr.f);
    printf("C [%s]\n", Game->attr.c);

    int max_width = 0;
    int line_len = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        Game->height++;  
        line_len = strlen(line);
        if (line_len > max_width)
        {
            max_width = line_len;
            Game->width = max_width; 
        }
        free(line);
    }

    printf("\nHEIGHT=%d WIDTH=%d\n", Game->height, Game->width);

    close(fd); 

    Game->map = (char **)calloc(Game->height, sizeof(char *));
    if (Game->map == NULL) 
    {
        ft_put_error("Error: Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    fd = open(argv, O_RDONLY);
    check_file_exists(argv, &fd);

    while ((line = get_next_line(fd)) && map_start > 1)
    {
        free(line); // Skipping attribute lines
        map_start--;
    }
    printf("MAP BEGINS HERE\n");

    int line_count = 0;
    while ((line = get_next_line(fd)))
    {
        if (inv_sym(line))
        {
            ft_put_error("Error: Invalid symbol found");
            exit(EXIT_FAILURE);
        }
        Game->map[line_count] = calloc(Game->width + 1, sizeof(char)); // +1  null
        if (Game->map[line_count] == NULL)
        {
            ft_put_error("Error: Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        strncpy(Game->map[line_count], line, strlen(line));
        free(line);
        line_count++;
    }

    close(fd);
}



void ft_print_map(struct game *Game)
{
    printf("Printing map\n");
    for (int i = 0; i < Game->height; i++)
    {
        printf("%s", Game->map[i]);
    }
    //printf("\n");
     printf("Height: %d\n", Game->height);
    printf("Width: %d\n", Game->width);
}



void	ft_put_error(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		write(STDERR_FILENO, &string[i], 1);
		i++;
	}
	write(STDERR_FILENO, "\n", 1);
	return ;
}

