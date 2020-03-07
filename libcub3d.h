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

# define    TILE_SIZE       64
# define    MINIMAP_SCALE   data.Width * 0.00009
# define    WHITE           16777215
# define    RED             9830400
# define    SKY 	        1008890
# define    FLOOR	        321600


# define    TRUE        1
# define    FALSE       0

typedef struct s_mlx
{
    void        *mlx;
    void        *window;
}               t_mlx;

typedef struct s_color
{
    int r;
    int g;
    int b;

    unsigned int color;
}             t_color;

typedef struct s_texture
{
    char        *north;
    char        *south;
    char        *west;
    char        *east;
    char        *sprite;
}               t_texture;


typedef struct s_player
{
    int         walkDirection;
    int         turnDirection;
    float       moveSpeed;
    float       rotationSpeed;
    float       fov;
    float       dirangle;
    float       x;
    float       y;
}               t_player;

typedef struct s_image
{
    int         width;
    int         height;
    int         bits_per_pixel;
    int         size_line;
    int         endian;
    void        *ptr;
    int         *data;
}               t_image;


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
    int         nb_of_rows;
    int         nb_of_cols;
    int         nb_of_sprites;
}               t_data;

typedef struct s_ray
{
	int         down;
	int         up;
	int         right;
	int         left;
}               t_ray;

typedef struct s_pos
{
    float       x;
    float       y;
    float       distance;
    int         wasHitVertical;
}               t_pos;

typedef struct s_sprites
{
    float       x;
    float       y;
    float       distance;
}               t_sprites;

float           ray_distance[2560];

t_ray           ray;
t_data          data;
t_mlx           mlx;
t_player        player;
t_image         image;
t_pos           wallhit;
t_pos           Texhit;
t_image         north;
t_image         west;
t_image         south;
t_image         east;
t_image         sprite;
t_sprites       s_data[50];
pid_t           x; 

int             g_look;

void	        set_hooks();
int             ft_update(char *argv);
void            ft_pixel_put(float x, float y, unsigned int color);
int             ft_read_map(char **str);
unsigned int    rgb_to_int(unsigned int r, unsigned int g, unsigned int b);
void            ft_draw_map(void);
void            ft_draw_player(void);
void            ft_Wall_Hit(int col, float rayAngle);
int             ft_hasWall(float x, float y);
float           ft_normalizeAngle(float *angle);
void            ft_draw_line(float X0, float Y0, float X1 , float Y1, unsigned int color);
void            ft_image_settings();
void            ft_draw_cube(int  x, int y);
void	        ft_drawmap();
float           ft_distanceBetweenPoints(float x1, float y1, float x2, float y2);
void            init_sprites();
void            init_ray();
void            init_player();
void            init_textures();
void            ft_position_update();
void            init_game(char **argv);
void            RayFacing(float angle);
void            ft_sprite(int i);
void            ft_draw_sprites(void);
void            ft_sort_sprites();
void            ft_handle_bmp();
int             main_process(char **argv);
int             ft_map_cols(char **map);
int             ft_hasWall_tex(float pos_x, float pos_y);
#endif