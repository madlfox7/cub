#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h> // read(); write();
# include <fcntl.h> // open();
# include <stdlib.h> // malloc(); free(); exit();
# include <stdio.h> // perror();
# include <math.h>




typedef struct attr_count
{
    int no_count;
    int so_count;
    int ea_count;
    int we_count;
    int c_count;
    int f_count;
} t_count;

typedef struct s_attributes
{
    t_count count;
    int attr_count;
    char *so;
    char *we;
    char *no;
    char *ea;
    char *f;
    char *c;
}t_attributes;

typedef struct s_player
{
    int x;
    int y;
}t_player;

struct game  
{
    t_attributes attr;
      t_player player;
    char **map;
    int map_x;
    int map_y;
    int height;
    int width;
};

void fix_player_pos(struct game *Game);
void	ft_put_error(char *string); 
int	ft_strncmp(const char	*s1, const char	*s2, size_t	n);
void	ft_check_argc_and_name(int argc, char *argv[]);
void check_file_exists(char *argv, int *fd);
void ft_print_map(struct game *Game);
void malloc_map(struct game *Game);
void get_lines(int fd, struct game *Game);
int empty_map(struct game *Game);
void ft_get_map(char *argv, struct game *Game);
int is_pl_pos(char c);
void check_map_sym(struct game *Game);
int is_space(char c);
void check_map_sym(struct game *Game);
void check_player_count(int player_count);
void ft_check_map(struct game *Game);
//void free_map(char **map, int height);
char	**ft_split(char const *s, char c, int *size, long *i);
long	word_len(char const *s, char c, long i);
void	free_memory(char **ptr_ss, long index);
unsigned int is_delim(char c, char *delim);
char *my_strtok(char *str, char *delim);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);
size_t	ft_strlen(char	*s);
void init_attributes(struct game *Game);
int is_valid_attr(struct game *Game, char *line);
int inv_sym(char *line);

void check_borders(struct game *Game, int ind, int jind);
int is_valid_symbol(char c);

void free_attributes(struct game *Game);
int is_valid_symbol(char c);
int check_attr_count(struct game *Game);
void free_map(struct game *Game);


int			check_attr_path(struct game *Game);

#endif