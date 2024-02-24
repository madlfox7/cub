#include "cub3d.h"


unsigned int is_delim(char c, char *delim)
{
    while(*delim != '\0')
    {
        if(c == *delim)
            return 1;
        delim++;
    }
    return 0;
}

char *my_strtok(char *str, char *delim)
{
    static char *backup_str;
    if(!str)
    {
        str = backup_str;
    }
    if(!str)
    {
        return NULL;
    }
     while(1)
    {
        if(is_delim(*str, delim))
        {
            str++;
            continue;
        }
        if(*str == '\0')
        {
            return NULL; 
        }
        break;
    }
    char *ret = str;
    while(1)
    {
        if(*str == '\0')
        {
            backup_str = str;
            return ret;
        }
        if(is_delim(*str, delim))
        {
            *str = '\0';
            backup_str = str + 1;
            return ret;
        }
        str++;
    }
}



////strtok vers 2


// char *my_strtok(char *str, const char *delim) {
//     static char *buffer = NULL;
//     if (str != NULL) buffer = str;
//     if (buffer == NULL || *buffer == '\0') return NULL;
//     char *token = buffer;
//     while (*buffer != '\0') {
//         if (strchr(delim, *buffer) != NULL) {
//             *buffer = '\0';
//             buffer++;
//             return token;
//         }
//         buffer++;
//     }
//     return token;
// }
