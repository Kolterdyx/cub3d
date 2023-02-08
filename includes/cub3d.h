/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:32:55 by cigarcia          #+#    #+#             */
/*   Updated: 2023/02/01 20:32:58 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 960.
# define HEIGHT 540.

# define FOV 60.
# define RAYS 960.
// Length in map units (1 * TILE_SIZE) of a ray
# define RAY_LENGTH 200.

# define MINIMAP_WIDTH 240.
# define MINIMAP_HEIGHT 240.
# define TILE_SIZE 20.

// These values here are a proportion of the minimap scale
# define PLAYER_SPEED 0.075
# define PLAYER_ROTATION_SPEED 0.001
# define PLAYER_HITBOX_RADIUS 0.25
# define PLAYER_INTERACTION_RADIUS 1.25

/**
 * @brief 2D vector
 */
typedef struct s_vector
{
	double			x;
	double			y;
}					t_vec;

/**
 * @brief A 2D edge (line segment) defined by two points.
 *
 * @param start Start point.
 * @param end End point.
 * @param tex_index Texture index for the texture to be rendered on this edge.
 * 0 = North, 1 = East, 2 = South, 3 = West, 4 = Door, 5 = Sprite
 */
typedef struct s_edge
{
	t_vec			start;
	t_vec			end;
	int				tex_index;
}					t_edge;

/**
 * @brief A door that can be opened and closed.
 *
 * @param edge Edge used to collide with the player.
 * @param open Whether the door is open or not.
 */
typedef struct s_door
{
	t_edge			edge;
	int				dir;
	int				open;
}					t_door;

/**
 * @brief Main structure for holding global data.
 *
 * @param mlx The mlx instance.
 * @param img The image to draw to.
 * @param floor_color The color of the floor (RGBA 32bit format).
 * @param ceiling_color The color of the ceiling (RGBA 32bit format).
 * @param edges Double linked list of wall_edges to intersect.
 * @param player_pos The player's position as a vector.
 * @param player_angle The player's angle in radians.
 * @param rays Double linked list of vectors that will be used for ray casting.
 * @param wall_textures Array of wall textures. Also includes the door because
 * it's easier that way. (0 = North, 1 = East, 2 = South, 3 = West, 4 = Door).
 *
 */

typedef struct s_parser
{
	char	**name;
	char	**value;
}			t_parser;

typedef struct t_data
{
	mlx_t			*mlx;
	mlx_image_t		*img;

	mlx_image_t		*minimap;

	uint32_t		floor_color;
	uint32_t		ceiling_color;
	t_list			*wall_edges;
	t_list			*doors;

	mlx_texture_t	**textures;
	t_vec			texture_size;

	t_vec			last_mousepos;

	t_vec			player_pos;
	double			player_angle;
	t_list			*rays;
	int				player_dir;
	char			**textures_path;
	t_list			*map;
}					t_data;

void				key_hook(mlx_key_data_t keydata, void *param);

/**
 * @brief Calculate the dot product of two vectors.
 * @param a
 * @param b
 * @return Dot product of a and b
 */
double				vec_dot(t_vec a, t_vec b);

/**
 * @brief Calculate the difference of two vectors.
 * @param a
 * @param b
 * @return The vector resulting from subtracting b from a
 */
t_vec				sub_vec(t_vec a, t_vec b);

/**
 * @brief Calculate the sum of two vectors.
 * @param a
 * @param b
 * @return The vector resulting from adding a and b
 */
t_vec				add_vec(t_vec a, t_vec b);

/**
 * @brief Scale a vector by a scalar.
 * @param a
 * @param b
 * @return The vector resulting from scaling a by b
 */
t_vec				vec_scl(t_vec a, double b);

/**
 * @brief Return the normalized vector of a.
 * @param a The vector to normalize
 * @return Unit vector of a
 */
t_vec				vec_unit(t_vec a);

/**
 * @brief Rotate a vector by an angle.
 * @param a Vector to rotate
 * @param angle Angle in radians
 * @return The vector resulting from rotating a by angle
 */
t_vec				vec_rotate(t_vec a, double angle);

/**
 * @brief Return a unit vector from an angle.
 * @param angle Angle in radians
 * @return The vector resulting from rotating (1, 0) by angle
 */
t_vec				vec_from_rad(double angle);

/**
 * @brief Calculate the angle of a vector.
 * @param a
 * @return The angle of a in radians
 */
double				vec_rad(t_vec a);

/**
 * @brief Calculate the length of a vector.
 * @param a
 * @return The length of a
 */
double				vec_len(t_vec a);

/**
 * @brief Calculate the distance between two vectors.
 * @param a
 * @param b
 * @return The distance between a and b (|a - b|)
 */
double				vec_dist(t_vec a, t_vec b);

/**
 * @Tell if a vector is empty.
 * @param a
 * @return Whether a is empty (a.x == 0 && a.y == 0)
 */
int					is_vector_empty(t_vec a);

/**
 * @brief Calculate the intersection of two wall_edges.
 * @param a
 * @param b
 * @param intersection Pointer to store the intersection point if it exists
 * @return Whether the wall_edges intersect
 */
int					edges_intersect(t_edge a, t_edge b, t_vec *intersection);

/**
 * @brief Check if there is an intersection between an edge and a circle
 * @param a The edge
 * @param center The center of the circle
 * @param radius The radius of the circle
 * @param closest_point The closest point on the edge to the center
 * of the circle
 * @return Whether the edge intersects the circle
 */
int					edge_intersects_circle(t_edge a, t_vec center,
						double radius, t_vec *closest_point);

/**
 * @brief Calculate the intersection of two wall_edges.
 * @param a
 * @param b
 * @return The intersection point if it exists, (0, 0) otherwise
 */
t_vec				find_intersection(t_edge a, t_edge b);

/**
 * @brief Create a new vector allocated on the heap. The returned vector can be
 * freed with the free() function.
 * @param x
 * @param y
 * @return Pointer to the new vector.
 */
t_vec				*vector_alloc(double x, double y);

/**
 * @brief Create a new edge allocated on the heap. The returned edge can be
 * freed with the free() function.
 * @param x
 * @param y
 * @return Pointer to the new edge.
 */
t_edge				*edge_alloc(t_vec start, t_vec end, int dir);

/**
 * @brief Create a copy of a vector. Can be used to create a copy on the heap
 * of a vector on the stack.
 * @param a
 * @return
 */
t_vec				*vec_cpy(t_vec a);

/**
 * @brief Basic initialization of the t_data structure.
 * @return Data structure with the MLX-related fields initialized.
 */
t_data				*init_data(void);

/**
 * @brief Initialize the player's position, direction, and rays.
 * @param data The data structure to modify.
 * @param pos The player's position.
 */
void				init_player(t_data *data, t_vec pos);

/**
 * @brief Create a new image from a cropped region of an existing texture.
 * @param texture The texture to crop.
 * @param origin The origin of the crop region.
 * @param size The size of the crop region.
 * @return An image of the cropped region.
 */
mlx_image_t			*cropped_texture(mlx_t *mlx, mlx_texture_t *texture,
						t_vec origin, t_vec size);

/**
 * @brief Scales the given image by the given scale factor
 * (x and y are independent).
 * Calculates the pixel value based on the NEAREST pixel
 * @param mlx MLX instance.
 * @param img MLX image to scale.
 * @param scale Scale vector (x for horizontal scale, y for vertical scale)
 * @return New scaled image.
 */
mlx_image_t			*scale_image(mlx_t *mlx, mlx_image_t *img, t_vec scale);

/**
 * @brief Gets the color value of a given pixel from the given image
 * (RGBA 32 bit).
 * @param image MLX image to get the pixel from.
 * @param x X coordinate of the pixel.
 * @param y Y coordinate of the pixel.
 * @return Color value of the pixel in RGBA 32bit format,
 * -1 if the pixel is out of bounds.
 */
uint32_t			mlx_get_pixel(mlx_image_t *image, int x, int y);

/**
 * @brief Given an area, scale and offset, crop, scale and display a texture on
 * the corresponding location
 * @param mlx MLX instance
 * @param img MLX image to draw to
 * @param texture Texture to crop, scale and offset
 * @param area This is an array of 4 t_vec. Here is an example: @code
 * (t_vec[4]){
 *     (t_vec){0, 0},    //area origin
 *     (t_vec){32, 32},  //area size
 *     (t_vec){1, 1},    //scale vector
 *     (t_vec){10, 10}   //offset vector
 * }
 * @endcode
 * This is what the norme makes us do :(
 *
 */
void				draw_texture_area_scaled(mlx_t *mlx, mlx_image_t *img,
						mlx_texture_t *texture, t_vec *area);

/**
 * @brief Given a bit set, and a bit count, reverses the bits.
 * @param set Set of bits. Can't be larger than a uint32_t.
 * @param count Number of bits to flip (from the right). The first bit will end
 * up at the position of the last bit, even if that happens to be in the middle
 * of the uint32_t.
 * @return Reversed bit set.
 */
uint32_t			revert_bits(uint32_t set, int count);

/**
 * @brief Given a value, the range it is currently in, and the desired range,
 * maps the value to be the same proportional value in the new range
 * @param value Value to map.
 * @param old_range Old/current range.
 * @param new_range New/desired range.
 * @return Mapped value.
 */
double				map_range(double value, t_vec old_range, t_vec new_range);

/**
 * @brief Fills and image with the given color.
 * @param img MLX image to fill.
 * @param color Color in RGBA 32 bit format.
 */
void				mlx_fill_image(mlx_image_t *img, uint32_t color);

/**
 * @brief Render logic goes here
 * @param data
 */
void				render(t_data *data);

/**
 * @brief Updates the minimap
 * @param data
 */
void				draw_calls(t_data *data);

/**
 * @brief Simple line-drawing function.
 * @param img MLX image to draw to.
 * @param edge Edge/segment to draw.
 * @param color Color of the line.
 */
void				draw_line(mlx_image_t *img, t_edge edge, uint32_t color);

/**
 * @brief Wrapper for @c mlx_put_pixel to avoid segfaults.
 * @param img
 * @param x
 * @param y
 * @param color
 */
void				put_pixel(mlx_image_t *img, int x, int y, uint32_t color);

/**
 * @brief Simple function for drawing circles
 * @param img
 * @param pos
 * @param radius
 * @param color
 */
void				draw_circle(mlx_image_t *img, t_vec pos, double radius,
						uint32_t color);

/**
 * @brief Calculate player collision with the map.
 * @param data
 */
void				collisions(t_data *data);

/**
 * @brief Add a wall to the map.
 * @param data
 * @param pos Position of the wall.
 * @param direction Cardinal direction of the wall (0 = north, 1 = east, 2 =
 * south, 3 = west).
 */
void				add_wall(t_data *data, t_vec pos, int direction);

/**
 * @brief Load a map from an integer array.
 * @param data
 * @param arr Integer array containing the map. (0 = empty, 1 = wall,
 * 2 = player, 3 = sprite, 4 = door (should only have two walls
 * around it on opposite sides))
 * @param shape
 */
void				init_map(t_data *data, const int *arr, t_vec shape);

/**
 * @brief Process raycasting for all rays.
 * @param data
 */
void				rays(t_data *data);

/**
 * @brief Draw a full rectangle.
 * @param img MLX image to draw to.
 * @param pos Start position of the rectangle.
 * @param size Size of the rectangle.
 * @param color Color of the rectangle in RGBA 32 bit format.
 */
void				draw_rectangle(mlx_image_t *img, t_vec pos, t_vec size,
						uint32_t color);

/**
 * @brief Get the velocity vector of the player based on a relative angle.
 * @param data
 * @param angle Relative angle in radians.
 * @return Velocity vector.
 */
t_vec				calc_velocity(t_data *data, double angle);

/**
 * Cursor hook
 * @param x
 * @param y
 * @param vdata
 */
void				cursor_hook(double x, double y, void *vdata);

/**
 * Returns a value from a 1D integer array given a 2D position.
 * @param pos 2D position.
 * @param arr Integer array.
 * @param width width of the matrix.
 * @param default_value default value to return if something went wrong.
 * @return
 */
int					arr_index(t_vec pos, const int *arr, int width,
						int default_value);

/**
 * Initialize door.
 * @param data
 * @param pos Position of the door.
 * @param shape Shape of the map.
 * @param arr Integer array representation of the map.
 */
void				init_door(t_data *data, t_vec pos, t_vec shape,
						const int *arr);

/**
 * Initialize sprite
 * @param data
 */
void				init_sprite(t_data *data);

/**
 * Mouse hook
 * @param key
 * @param action
 * @param mod
 * @param vdata
 */
void				mouse_hook(mouse_key_t key, action_t action,
						modifier_key_t mod, void *vdata);

/**
 * Render images based on ray casts.
 * @param data
 * @param dir Direction of the intersection
 * @param inter Position of the intersection
 * @param ray_index Index of the ray
 */
void				render_ray(t_data *data, int dir, t_vec inter,
						int ray_index);

/**
 * Draw the wall section corresponding to hit_pos
 * @param data
 * @param rect rect.start is the position on the texture. rect.end
 * is the area of the texture
 * @param hit_pos Hit position of the ray normalized to [0, TILE_SIZE)
 */
void				render_wall(t_data *data, t_edge rect, t_vec hit_pos);

/**
 * Given a coordinate vector and a direction, get the texture position at which
 * the ray landed.
 * @param pos Coordinate vector
 * @param dir Direction (0 = North, 1 = East, 2 = South, 3 = West)
 * @return
 */
t_vec				wall_pos(t_vec pos, int dir);

/**
 * @brief Create an RGBA 32 bit color from 3 separate values. Alpha channel is
 * fixed to 255.
 * @param r Red channel. (0-255)
 * @param g Green channel. (0-255)
 * @param b Blue channel. (0-255)
 * @return Color in RGBA 32 bit format.
 */
uint32_t			rgb_to_int(int r, int g, int b);

/**
 * @brief Parse a map file.
 * @param info Struct used to store different data.
 * @param argv Arguments.
 * @param map_arr Pointer to map contents array.
 * @param dimensions Pointer to map dimensions.
 * @return Boolean, whether the map was successfully parsed or not.
 */
int			parser(t_data *info, char **argv, int **map_arr, t_vec *dimensions);

int			first_part_check(char **file, int *j, t_data *info);

char		**second_part_check(char **file, t_data *info);

char		*ft_strjoin_free(char *str1, const char *str2);

int			condition(char c);

int			map_filler(char **map, int **map_arr, t_vec *dimensions);

void		ft_print_data(int *map, t_vec dimensions);

void		ft_charpp_printf(char **charpp);

void		set_char(char *str, int start, int end, char c);

void		ft_parser_error(char *str);

int			get_player_dir(char c, int *flag);

t_list				*ft_lsti(t_list *lst, int index);

#endif //CUB3D_H
