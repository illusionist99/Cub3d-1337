#ifndef     LIBCUB3D_H
# define    LIBCUB3D_H


#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <mlx.h>
#include "ft_printf/libftprintf.h"
#include "gnl/get_next_line.h"


# define    EXIT_KEY  53
# define    KEY_LEFT  123
# define    KEY_RIGHT 124
# define    KEY_DOWN  125
# define    KEY_UP    126

# define    WINDOW_WIDTH    900
# define    WINDOW_HEIGHT   900
# define    TILE_SIZE       32

# define    WHITE     16777215
# define    RED       9830400

# define    TRUE        1
# define    FALSE       0

typedef struct s_mlx
{
    void    *mlx;
    void    *window;
}               t_mlx;

typedef struct s_color
{
    unsigned int r;
    unsigned int g;
    unsigned int b;

    unsigned int color;
}             t_color;

typedef struct s_texture
{
    char *north;
    char *south;
    char *west;
    char *east;
    char *sprite;
}               t_texture;


typedef struct s_player
{
    int     walkDirection;
    int     turnDirection;
    int     radius;
    float   rotationAngle;
    float   moveSpeed;
    float   rotationSpeed;
    float   fov;
    float   dirangle;
    int     x;
    int     y;
}               t_player;

typedef struct s_data
{
    int         Width;
    int         Height;
    t_texture   Path;
    t_color     floor;
    t_color     ceilling;
    char        *map[50];
    int         cols;
    int         index;
}               t_data;

t_data      data;
t_mlx       mlx;
t_player    player;


void	        set_hooks();
int             ft_update();
int             ft_read_map(char **str);
unsigned int    rgb_to_int(unsigned int r, unsigned int g, unsigned int b);
void            ft_draw_map(void);
void            ft_draw_player(void);
float           ft_Wall_Hit(int col, float rayAngle);
int             ft_hasWall(float x, float y);
float           ft_normalizeAngle(float *angle);
void            ft_draw_line(float X0, float Y0, float X1 , float Y1);
void            ft_wall_casting(int col, float angle, int wasVert, float wallx, float wally);
#endif