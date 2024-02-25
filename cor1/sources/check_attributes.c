#include "cub3d.h"
#include <string.h> //change strlen and strdup

int check_attr_count(struct game *Game)
{
//    struct attr_count count = Game->attr.count;

//return (Game->attr.count.f_count == 1 && Game->attr.count.c_count == 1);
     return ((Game->attr.count.no_count >= 1)
     && Game->attr.count.so_count  >= 1 && Game->attr.count.we_count  >= 1 &&
            Game->attr.count.ea_count  >= 1 && Game->attr.count.f_count  >= 1 && Game->attr.count.c_count  >= 1);
//if at least one path for all attributes present, stop parsing

}



int is_attr(char *line)
{
  //  printf ("LINE****************************:%s\n", line);
   //  printf ("LINE****************************:%zu\n", ft_strlen(line));
  if (ft_strlen(line) < 2 && (line[0] != 'F' && line[0] != 'C')) 
        return 0;
    if ((strncmp(line, "NO", ft_strlen(line)) == 0 )||
        strncmp(line, "SO", ft_strlen(line)) == 0 ||
        strncmp(line, "WE", ft_strlen(line)) == 0 ||
        strncmp(line, "EA", ft_strlen(line)) == 0 ||
        strncmp(line, "F", ft_strlen(line)) == 0 ||
        strncmp(line, "C", ft_strlen(line)) == 0)
        {
           // printf("|%s|\n", line);
          //  printf("FOUND Attr\n\n");
            return 1;
        }
    return 0;
}


void init_attributes(struct game *Game)
{
    Game->attr_line = 0;
    Game->height = 0;
    Game->width = 0;
    Game->attr.count.no_count = 0;
    Game->attr.count.so_count = 0;
    Game->attr.count.we_count = 0;
    Game->attr.count.ea_count = 0;
    Game->attr.count.f_count = 0;
    Game->attr.count.c_count = 0;
    Game->attr.attr_count = 0;
    Game->attr.so = NULL;
    Game->attr.we = NULL;
    Game->attr.no = NULL;
    Game->attr.ea = NULL;
    Game->attr.f = NULL;
    Game->attr.c = NULL;
}


void free_attributes(struct game *Game)
{
    free(Game->attr.so);
    free(Game->attr.we);
    free(Game->attr.no);
    free(Game->attr.ea);
    free(Game->attr.f);
    free(Game->attr.c);
}

void assign_attr(struct game *Game, char *type, char *path)
{
    if (strncmp(type, "NO", strlen(type)) == 0)
    {
        Game->attr.no = strdup(path);
        Game->attr.count.no_count++;
    } 
    else if (strncmp(type, "SO", strlen(type)) == 0)
    {
        Game->attr.so = strdup(path);
        Game->attr.count.so_count++;
    } 
    else if (strncmp(type, "WE", strlen(type)) == 0)
    {
        Game->attr.we = strdup(path);
        Game->attr.count.we_count++;
    }
    else if (strncmp(type, "EA", strlen(type)) == 0)
    {
        Game->attr.ea = strdup(path);
        Game->attr.count.ea_count++;
    } 
    else if (strncmp(type, "F", strlen(type)) == 0)
    {
        Game->attr.f = strdup(path);
        Game->attr.count.f_count++;
    } 
    else if (strncmp(type, "C", strlen(type)) == 0)
    {
        Game->attr.c = strdup(path);
        Game->attr.count.c_count++;
    }
}


int is_attribute(struct game *Game, char *line)
{
    char *delim = " \t\n\v\f\r";
    char *token = my_strtok(line, delim);
    char *type = NULL;
    int word_count = 0;


    while (token)
    {
       printf("Token [%s]\n", token);
        if (word_count == 0)
        {
            if (is_attr(token)) //line starts from attr 
                type = token;
            else
            {
                printf("STOP MAP FOUND\n"); //assume it's map start
                return 0;
            }
        }
        else if (word_count == 1)
            assign_attr(Game, type, token);
        else //if word_count not 0 and not 1
        {
            ft_put_error("!!!!Error: Invalid attribute: too many arguments for attr\n");
            exit(EXIT_FAILURE);
        }
        token = my_strtok(NULL, delim);
        word_count++;
    }
   if (word_count == 1)
   {
         printf("Attribute identifier missing\n");
         exit(1);
   }
  //printf("!!!!!!!!!!!!!!!!!!!!!!!!Word count [%d]\n", word_count);
    return 1;
}

