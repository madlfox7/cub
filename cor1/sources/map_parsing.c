#include "cub3d.h"


int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

void check_map_sym(struct game *Game)
{
    int i = 0;
    int j = 0;
    while (i < Game->height)
    {
        j = 0;
        while (j < Game->width)
        {
            if (Game->map[i][j] != '0' && Game->map[i][j] != '1' && !is_space(Game->map[i][j]) && !is_pl_pos(Game->map[i][j]))
            {
                ft_put_error("Error: Invalid map symbol\n");
                exit(EXIT_FAILURE);
            }
            j++;
        }
        i++;
    }
}


void check_player_count(int player_count)
{
    if (player_count != 1)
    {
        ft_put_error("Error:\n");
        if (player_count == 0)
            ft_put_error("Player position not found\n");
        else
            ft_put_error("Multiple player positions found\n");
        exit(EXIT_FAILURE);
    }
}

void fix_player_pos(struct game *Game)
{
    int i = 0;
    int j = 0;
    int player_count = 0;

    while (i < Game->height)
    {
        j = 0;
        while (j < Game->width)
        {
            if (is_pl_pos(Game->map[i][j]))
            {
                player_count++;
                Game->player.x = i;
                Game->player.y = j;
            }
            j++;
        }
        i++;
    }
    check_player_count(player_count);
   
}




int inv_sym(char *line)
{
    int i = 0;
    while (line[i])
    {
        if (!is_space(line[i]) && !is_valid_symbol(line[i]))
        {
            printf("Error: Invalid symbol found: %c\n in line [%s]\n", line[i], line);
            exit(1);
          //  return 1; // Invalid symbol found
        }
        i++;
    }
    return 0; // No invalid symbols found
}


int is_valid_symbol(char c)
{
    char *valid_symbols = " NSWE10\n\r\f\v\t";
    int num_symbols = ft_strlen(valid_symbols);
    for (int i = 0; i < num_symbols; ++i)
    {
        if (c == valid_symbols[i])
            return 1;
    }
    return 0;
}


#include <stdbool.h>

bool empty_line(char *line) 
{
    while (*line != '\0') {
        if (*line != ' ' && *line != '\t' && *line != '\n') {
            return false; // Not an empty line
        }
        line++;
    }
    return true; // Empty line
}





void map_in_the_end(struct game *Game)
{
    int map_started = 0;
    int prev_map_start = -1; 
    for (int i = 0; i < Game->height; i++)
    {
        int line_contains_map_data = 0;

        for (int j = 0; j < Game->width; j++)
        {
            if (Game->map[i][j] == '1' || is_pl_pos(Game->map[i][j]) || Game->map[i][j] == '0')
            {
                line_contains_map_data = 1;
                break;
            }
        }
        if (line_contains_map_data && !empty_line(Game->map[i]))
        {
            if (!map_started)
            {
                printf("MAP STARTED in line %d\n", i);
                map_started = 1;
                prev_map_start = i; 
            }
            else
            {
                if (i - prev_map_start != 1)
                {
                    ft_put_error("Error: Map is disconnected\n");
                    exit(EXIT_FAILURE);
                }
                prev_map_start = i; 
            }
        }
    }

    if (!map_started)
    {
        ft_put_error("Error: Map is empty\n");
        exit(EXIT_FAILURE);
    }
}



void ft_check_map(struct game *Game)
{
    printf("Checking map\n");

    fix_player_pos(Game);
    map_in_the_end(Game); //check if map is in the end
    printf("height %d\n width %d\n", Game->height, Game->width);
    for (int i = 0; i < Game->height; i++)
    {
        for (int j = 0; j < Game->width; j++)
        {
            if ((i == 0 || j == 0 || i == Game->height - 1 || j == Game->width - 1) && (Game->map[i][j] == '0' || is_pl_pos(Game->map[i][j])))
            {
                ft_put_error("Error: Map is not closed\n");
                exit(EXIT_FAILURE);
            }
            if (Game->map[i][j] == ' ' || Game->map[i][j] == '\0' || Game->map[i][j] == '\n' || Game->map[i][j] == '\t')
            {
                check_borders(Game, i, j);
               // printf("i [%d] j [%d]\n", i, j);
            }
        }
    }
   
}


int empty_map(struct game *Game)
{
    int i = 0;

    if (Game->height == 0 || Game->width == 0)
        return 1;
    while (i < Game->height)
    {
        char *line = Game->map[i];
        while (*line)
        {
            if (*line != ' ' && *line != '\n') //not empty map 
                return 0; 
            line++;
        }
        i++;
    }
    return 1;  //empty map
}