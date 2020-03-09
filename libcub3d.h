/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 08:52:37 by malaoui           #+#    #+#             */
/*   Updated: 2020/03/09 17:53:33 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBCUB3D_H
# define LIBCUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include "ft_printf/libftprintf.h"
# include "gnl/get_next_line.h"
# include <signal.h>
# include <sys/wait.h>

# define EXIT_KEY		53
# define KEY_LEFT		0
# define KEY_RIGHT		2
# define KEY_DOWN		1
# define KEY_UP			13
# define KEY_LOOKUP		126
# define KEY_LOOKDOWN	125
# define TILE_SIZE		64
# define MINIMAP_SCALE	g_data.width * 0.00009
# define WHITE 			16777215
# define RED 			9830400
# define TRUE 			1
# define FALSE			0

typedef struct			s_mlx
{
	void				*mlx;
	void				*window;
}						t_mlx;

typedef struct			s_color
{
	int					r;
	int					g;
	int					b;
	unsigned int		color;
}						t_color;

typedef	struct			s_texture
{
	char				*north;
	char				*south;
	char				*west;
	char				*east;
	char				*sprite;
}						t_texture;

typedef struct			s_player
{
	int					walkdirection;
	int					turndirection;
	float				movespeed;
	float				rotationspeed;
	float				fov;
	float				dirangle;
	float				x;
	float				y;
}						t_player;

typedef struct			s_image
{
	int					width;
	int					height;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	void				*ptr;
	int					*data;
}						t_image;

typedef struct			s_data
{
	int					width;
	int					height;
	t_texture			path;
	t_color				floor;
	t_color				c;
	char				*map[50];
	int					cols;
	int					index;
	int					nb_of_rows;
	int					nb_of_cols;
	int					nb_of_sprites;
}						t_data;

typedef struct			s_ray
{
	int					down;
	int					up;
	int					right;
	int					left;
}						t_ray;

typedef struct			s_pos
{
	float				x;
	float				y;
	float				distance;
	int					washitvertical;
}						t_pos;

typedef struct			s_sprites
{
	float				x;
	float				y;
	float				distance;
}						t_sprites;

typedef	struct			s_dir
{
	float				x;
	float				y;
}						t_dir;

typedef	struct			s_elem
{
	t_dir				intercept;
	t_dir				step;
	t_dir				exttouch;
	t_dir				wallhit;
}						t_elem;

typedef	struct			s_run
{
	float				xintercept;
	float				yintercept;
	float				xstep;
	float				ystep;
	float				foundhorzwallhit;
	float				horzwallhitx;
	float				horzwallhity;
	float				foundvertwallhit;
	float				vertwallhitx;
	float				vertwallhity;
	float				nexthorztouchx;
	float				nexthorztouchy;
	float				nextverttouchx;
	float				nextverttouchy;
	float				horzhitdistance;
	float				verthitdistance;
}						t_run;

typedef struct			s_line
{
	float				x0;
	float				y0;
	float				x1;
	float				y1;
	int					dx;
	int					dy;
	int					steps;
	float				xinc;
	float				yinc;
	float				x;
	float				y;
}						t_line;

int						g_nb_p;
float					g_ray_distance[2561];
t_ray					g_ray;
t_data					g_data;
t_mlx					g_mlx;
t_player				g_player;
t_image					g_image;
t_pos					g_wallhit;
t_pos					g_texhit;
t_image					g_north;
t_image					g_west;
t_image					g_south;
t_image					g_east;
t_image					g_sprite;
t_sprites				g_s_data[50];
pid_t					g_child;
int						g_save;
int						g_look;

int						ft_find_biggest_line(void);
void					set_hooks(void);
int						ft_update(char *argv);
void					ft_pixel_put(int x, int y, unsigned int color);
int						ft_read_map(char **str);
unsigned int			rgb_to_int(unsigned int r,
unsigned int g, unsigned int b);
void					ft_draw_map(void);
void					ft_draw_player(void);
void					ft_wall_hit(int col, float rayangle);
int						ft_haswall(float pos_x, float pos_y);
float					ft_normalizeangle(float *angle);
void					ft_draw_line(t_line line, unsigned int color);
void					ft_image_settings(void);
void					ft_draw_cube(int x, int y);
void					ft_drawmap(void);
float					ft_distancebetweenpoints(float x1, float y1,
float x2, float y2);
void					init_sprites(void);
void					init_ray(void);
void					init_player(void);
void					init_textures(void);
void					ft_position_update(void);
void					init_game(char **argv);
void					rayfacing(float angle);
void					ft_sprite(int i);
void					ft_draw_sprites(void);
void					ft_sort_sprites(void);
void					ft_handle_bmp(void);
int						main_process(char **argv);
int						ft_map_cols(char **map);
int						ft_haswall_tex(t_dir *pos);
void					ft_reset_struct(void);
int						horz_intersection(int col, float rayangle);
int						vert_intersection(int col, float rayangle);
void					ft_get_distance(int col,
t_dir horzwallhit, t_dir vertwallhit);
void					ft_draw_texture(t_image ptr, int col,
float offset, float wallstripheight);
int						ft_texture_draw(int col, float rayangle);
t_run					*ft_horz(t_run *mdr, float rayangle);
void					ft_horz_inc(t_run *mdr);
void					ft_draw_texture(t_image ptr, int col,
float offset, float wallstripheight);
int						exit_hook(int keycode, void *param);
void					ft_c(char *str);
void					ft_floor(char *str);
unsigned int			shadow(unsigned int color, int col);
void					ft_free_map(int n, char *error_msg);
int						ft_check_valid(char *s, int m_index);
void					ft_free(int n, char *s);
void					ft_free_sprites(t_texture *ptr);
int						ft_check_maze(void);
void					ft_free_struct(t_image *ptr);
int						ft_check_name(char *s);
int						ft_check_for_error(char *s, int m_index);
#endif
