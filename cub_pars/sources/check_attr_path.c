#include "cub3d.h"
#include <ctype.h>


int ft_isdigit(int c) 
{
    return (c >= '0' && c <= '9');
}

int simple_atoi(char *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-')
    {
        sign = -1;
        i++;
    }
    while (str[i] != '\0')
    {
        int digit = str[i] - '0';
        result = result * 10 + digit;
        i++;
    }
    return sign * result;
}

int invalid_color(char *token) 
{
    for (int i = 0; token[i] != '\0'; i++)
    {
        if (!ft_isdigit(token[i]))
            return 1;
    }
    int value = simple_atoi(token);

    if (value < 0 || value > 255)
        return 1;
    return 0;
}
#include <string.h>

int check_color(char *line) 
{
    char *color = strdup(line);
    size_t length = ft_strlen(color);
    if (color[length - 1] == ',') 
        return 0;

    char *token = my_strtok(color, ",");
    int counter = 0;

    while (token != NULL)
    {
        if (invalid_color(token))
            return 0;
        token = my_strtok(NULL, ",");
        counter++;
    }

    if (counter != 3)
        return 0;

    return 1;
}


int check_attr_path(struct game *Game)
{
    (void)Game;
    if (!check_color(Game->attr.f) || !check_color(Game->attr.c)) {
        ft_put_error("\nInvalid color\n");
        exit(1);
    }

    // Check other attribute paths like 'no', 'so', 'ea', 'we'
    // If they are not valid or don't end with '.xpm', exit(1)

    return 1;
}
