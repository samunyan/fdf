/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:28:59 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 13:43:01 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <float.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>

# define DEFAULT_WIDTH			1000
# define DEFAULT_HEIGHT			1000
# define DEFAULT_N_IMAGES		2
# define DEFAULT_COLOR   		0x00FFFFFF
# define DEFAULT_BG_COLOR 		0x00112d31

# define MAX_LINE				4096
# define USAGE					"Usage: ./fdf <filename>.fdf"
# define MAP_ERROR				"Map error"

typedef enum e_coord_sys
{
	LOCAL = 0,
	WORLD = 1,
	SCREEN = 2,
	RASTER = 3
}	t_coord_sys;

typedef struct s_3d
{
	float	x;
	float	y;
	float	z;
}	t_3d;

typedef struct s_2d
{
	float	x;
	float	y;
}	t_2d;

typedef struct s_vertex
{
	t_3d	local;
	t_3d	world;
	t_2d	screen;
	t_2d	raster;
}				t_vertex;

typedef struct s_map
{
	int			dim_x;
	int			dim_y;
	t_vertex	**points;
	float		scale;
}	t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_scene
{
	int			width;
	int			height;
	void		*mlx;
	void		*win;
	t_img		*images;
	int			current_image;
	t_map		map;
}	t_scene;

# ifdef __APPLE__

typedef enum e_event
{
	ON_KEYDOWN = 2,
	ON_DESTROY = 17,
	NOTIFY_MASK = 0,
	KEYPRESS_MASK = 0
}	t_event;

typedef enum e_keycode
{
	KEY_ESC = 53
}	t_keycode;

# else

typedef enum e_event
{
	ON_KEYDOWN = 2,
	ON_DESTROY = 17,
	NOTIFY_MASK = 1L<<17,
	KEYPRESS_MASK = 1L<<0
}	t_event;

typedef enum e_keycode
{
	KEY_ESC = 0xff1b
}	t_keycode;

# endif

t_scene	*init_scene(int width, int height, char *filename);
bool	is_valid_file_extension(char *filename, char *extension);
int		init_map(t_map *map, char *filename, int width, int height);
int		init_vertex_arrays(t_map *map, char **data);
int		init_display(t_scene *scene, char *name);
int		init_images(t_scene *scene);

int		open_map_file(char *filename);
int		get_map_dimensions(char *filename, int *dim_x, int *dim_y);
char	**get_map_data(char *filename);

void	geometry_to_origin(t_scene *scene);
void	local_to_world(t_scene *scene);
void	world_to_screen(t_scene *scene);
void	screen_to_raster(t_scene *scene);
void	apply_transform(t_scene *scene, float mat[4][4], int from, int to);
void	project(t_3d *p_world, t_2d *p_screen);

bool	is_valid_pixel(t_2d *pixel, int width, int height);
float	get_steps(float delta_x, float delta_y);
void	image_pixel_put(t_img *image, int x, int y, int color);
void	draw_map(t_scene *scene);
void	fill_background(t_img *image, int width, int height, int color);
int		get_index_of_next_image(t_scene *scene);

void	handle_events(t_scene *scene);

t_3d	*get_3dpoint(t_vertex *point, int coord_sys);
t_2d	*get_2dpoint(t_vertex *point, int coord_sys);

void	set_point(t_3d *point, float x, float y, float z);
void	vec_copy(t_3d *src, t_3d *dst);
void	mat_mult_mat(float mat1[4][4], float mat2[4][4], float dest[4][4]);
void	vec_mult_mat(t_3d *src, float mat[4][4], t_3d *dst);
void	mat_identity(float mat[4][4]);
void	mat_translate(float matrix[4][4], float tx, float ty, float tz);
void	mat_scale(float matrix[4][4], float sx, float sy, float sz);

int		render_scene(t_scene *scene);
void	free_scene(t_scene **scene);

void	err_msg(bool errnoflag, int errnum, const char *msg);

#endif
