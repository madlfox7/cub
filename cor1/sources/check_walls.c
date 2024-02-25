#include "cub3d.h"




int isValid(int row, int col, struct game *Game)
{
    return (row >= 0 && row < Game->height && col >= 0 && col < Game->width);
}



int is_pl_pos(char c)
{
    return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

void check_borders(struct game *Game, int ind, int jind)
{
    int **moves = malloc(8 * sizeof(int *));
    for (int i = 0; i < 8; i++) {
        moves[i] = malloc(2 * sizeof(int));
    }
    moves[0][0] = -1; moves[0][1] = 0;   // Up
    moves[1][0] = -1; moves[1][1] = -1;  // Up-Left
    moves[2][0] = -1; moves[2][1] = 1;   // Up-Right
    moves[3][0] = 1;  moves[3][1] = 0;   // Down
    moves[4][0] = 1;  moves[4][1] = -1;  // Down-Left
    moves[5][0] = 1;  moves[5][1] = 1;   // Down-Right
    moves[6][0] = 0;  moves[6][1] = -1;  // Left
    moves[7][0] = 0;  moves[7][1] = 1;   // Right
    

    for (int k = 0; k < 8; k++)
    {
        int new_ind = ind + moves[k][0];
        int new_jind = jind + moves[k][1];

        if (isValid(new_ind, new_jind, Game) && (Game->map[new_ind][new_jind] == '0' || is_pl_pos(Game->map[new_ind][new_jind])))
        {
            printf("i [%d] j [%d]\n", ind, jind);
            ft_put_error("Error: map is not closed\n");
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < 8; i++) 
        free(moves[i]);
    free(moves);
}
