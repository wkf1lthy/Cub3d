#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <ctype.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>

# define NULL ((void *)0)
# define NB_TEXT 5
# define TILE_SIZE 64
# define WIDTH 1000
# define HEIGHT 800
# define FOV (66 * (M_PI / 180))

typedef struct s_coord
{
	double			x;
	double			y;
}					t_coord;

typedef struct s_coord_int
{
	int				x;
	int				y;
}					t_coord_int;

typedef struct s_rgb
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
}					t_rgb;

typedef struct s_dda
{
	t_coord			ray_dir;
	t_coord			side_dist;
	t_coord			delta_dist;
	t_coord			step;
	t_coord_int		map;
	int				hit;
	int				side;
}					t_dda;

typedef struct s_flash_light
{
	t_coord			player_dir;
	double			dst_factor;
	double			ray_dir_norm;
	double			player_dir_norm;
	double			scalar_product;
	double			angle_factor;
	double			falloff;
	double			light_factor;
}					t_flash_light;

typedef struct s_raycast
{
	t_coord			pos_ray;
	double			distance;
	int				wall_height;
	double			fish_eye;
	double			projected_wall_height;
	int				y_start;
	int				y_end;
	t_coord_int		texture_coord;
	int				tex_index;
	uint8_t			*pixel;
	int				color;
	int				hit_vertical;
	int				step_x;
	int				step_y;
	double			perp_wall_dist;
	int				wall_face;
	t_dda			dda;
}					t_raycast;

typedef struct s_sprite
{
	double			x;
	double			y;
	int				texture_id;
	double			distance;
}					t_sprite;

typedef struct s_all
{
	double			fov;
	t_coord			player_pos;
	double			player_angle;
	int				starting_dir;
	char			**map;
	int				width_map;
	char			**infos;
	mlx_texture_t	*tab_textures[NB_TEXT];
	mlx_t			*mlx;
	int				f;
	int				c;
	int				no;
	int				so;
	int				we;
	int				ea;
	int				d;
	int				color_c;
	int				color_f;
	int				last_cursor_x;
	mlx_image_t		*minimap_img;
	mlx_image_t		*wall_img;
	bool			minimap_visible;
	bool			fov_mouse;
	bool			sprint;
	bool			night_vision;
	mlx_image_t		*text_img;
	t_raycast		*raycast;
}					t_all;

void				check_args(int ac, char **av);
void				parsing(t_all **all, int ac, char **av);
void				init_player_position(t_all **all);
void				fill_tab(t_all **all, char *filename);
void				check_file(t_all **all);
void				init_ptr(t_all **all);
int					is_allowed_char(char c);
int					only_spaces(char *str);
void				exit_error(char *str);
void				ft_all_exit(t_all *all, char *str);
void				free_tab(char **tab);
int					check_format(char *str, char *cmp);
void				free_all(t_all *all);
void				update_count(t_all **all, char *id);
int					valid_path(char *path, t_all **all, int index);
int					id_line(char *line, t_all **all, int i);
int					get_line(char *line);
void				is_info_valid(t_all **all, char *line);
int					ft_isspace(char c);
int					is_map_closed(char **map);
int					forbidden_char(char **map);
int					is_border(int i, int j, int height, int len);
int					is_invalid_space(char **map, int i, int j, int height);
int					is_line_map(t_all *all, char *line, int fd);
char				**add_line(char **map, char *line);
void				check_map_valid(t_all **all);
void				adding_line(t_all **all, int fd, int flag);
int					setting_color(char *line);
int					valid_number(char *str);
void				update_color(t_all **all, char *color, char id);
void				is_valid_color(t_all **all, char *line);
int					setting_color(char *line);
char				*ft_strstr(const char *str1, const char *str2);

void				move_forward(t_all *all);
void				move_backward(t_all *all);
void				move_left(t_all *all);
void				move_right(t_all *all);
void				choice_move(void *param);
void				rotate_right(t_all *all);
void				rotate_left(t_all *all);
void				fov_mooves(void *param);
void				toggle_cursor(mlx_key_data_t keydata, void *param);
void				toggle_door(mlx_key_data_t keydata, void *param);

uint32_t			choose_color(char c);
void				player_on_minimap(t_all *all);
void				draw_minimap(t_all *all);
void				refresh_image(mlx_t *mlx, mlx_image_t **image);
void				init_ray(t_all *all, t_raycast *ray, double ray_angle);
void				draw_wall(t_all *all, t_raycast *ray, int x);
void				dda(t_all *all, t_raycast *ray, double ray_angle);
void				ray_cast(void *param);
void				escape(void *param);
void				check_wall_face(t_raycast *raycast);
void				calcul_tex(t_all *all, t_raycast *ray, int y);
void				calculate_color(mlx_texture_t **texture_tab,
						t_raycast *raycast);
int					mapping(char **map, size_t max_len, int height);
int					check_start_pos(char **map);
int					main(int ac, char **av);

#endif
