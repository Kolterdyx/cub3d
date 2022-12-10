/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:32:55 by cigarcia          #+#    #+#             */
/*   Updated: 2022/12/10 16:08:56 by cigarcia         ###   ########.fr       */
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

# define WIDTH 640
# define HEIGHT 480
# define FOV 60.0
# define RAYS 600

/**
 * @brief 2D vector
 *
 */
typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

/**
 * @brief A 2D edge (line segment) defined by two points.
 *
 * @param start Start point.
 * @param end End point.
 * @param dir Cardinal direction of the edge (the wall it represents).
 * 0 = North, 1 = East, 2 = South, 3 = West.
 */
typedef struct s_edge
{
	t_vector	start;
	t_vector	end;
	int			dir;
}				t_edge;

/**
 * @brief Main structure for holding global data.
 *
 * @param mlx The mlx instance.
 * @param img The image to draw to.
 * @param floor_color The color of the floor (RGBA 32bit format).
 * @param ceiling_color The color of the ceiling (RGBA 32bit format).
 * @param edges Double linked list of edges to intersect.
 * @param player_pos The player's position as a vector.
 * @param player_dir The player's direction as a unit vector.
 * @param rays Double linked list of vectors that will be used for ray casting.
 *
 */
typedef struct t_data
{
	mlx_t			*mlx;
	mlx_image_t		*img;

	uint32_t		floor_color;
	uint32_t		ceiling_color;
	t_list			*edges;

	mlx_texture_t	*wall_north;
	mlx_texture_t	*wall_south;
	mlx_texture_t	*wall_east;
	mlx_texture_t	*wall_west;

	t_vector		player_pos;
	t_vector		player_dir;
	t_list			*rays;
}				t_data;

void			key_hook(mlx_key_data_t keydata, void *param);

/**
 * @brief Calculate the dot product of two vectors.
 * @param a
 * @param b
 * @return Dot product of a and b
 */
double			dot_product(t_vector a, t_vector b);

/**
 * @brief Calculate the difference of two vectors.
 * @param a
 * @param b
 * @return The vector resulting from subtracting b from a
 */
t_vector		vector_sub(t_vector a, t_vector b);

/**
 * @brief Calculate the sum of two vectors.
 * @param a
 * @param b
 * @return The vector resulting from adding a and b
 */
t_vector		vector_add(t_vector a, t_vector b);

/**
 * @brief Scale a vector by a scalar.
 * @param a
 * @param b
 * @return The vector resulting from scaling a by b
 */
t_vector		vector_scale(t_vector a, double b);

/**
 * @brief Return the normalized vector of a.
 * @param a The vector to normalize
 * @return Unit vector of a
 */
t_vector		vector_normalize(t_vector a);

/**
 * @brief Rotate a vector by an angle.
 * @param a Vector to rotate
 * @param angle Angle in radians
 * @return The vector resulting from rotating a by angle
 */
t_vector		vector_rotate(t_vector a, double angle);

/**
 * @brief Return a unit vector from an angle.
 * @param angle Angle in radians
 * @return The vector resulting from rotating (1, 0) by angle
 */
t_vector		vector_from_angle(double angle);

/**
 * @brief Calculate the angle of a vector.
 * @param a
 * @return The angle of a in radians
 */
double			vector_angle(t_vector a);

/**
 * @brief Calculate the length of a vector.
 * @param a
 * @return The length of a
 */
double			vector_length(t_vector a);

/**
 * @brief Calculate the distance between two vectors.
 * @param a
 * @param b
 * @return The distance between a and b (|a - b|)
 */
double			vector_distance(t_vector a, t_vector b);

/**
 * @Tell if a vector is empty.
 * @param a
 * @return Whether a is empty (a.x == 0 && a.y == 0)
 */
int				is_vector_empty(t_vector a);

/**
 * @brief Calculate the intersection of two edges.
 * @param a
 * @param b
 * @param intersection Pointer to store the intersection point if it exists
 * @return Whether the edges intersect
 */
int				edges_intersect(t_edge a, t_edge b, t_vector *intersection);

/**
 * @brief Calculate the intersection of two edges.
 * @param a
 * @param b
 * @return The intersection point if it exists, (0, 0) otherwise
 */
t_vector		find_intersection(t_edge a, t_edge b);

/**
 * @brief Create a new vector allocated on the heap. The returned vector can be
 * freed with the free() function.
 * @param x
 * @param y
 * @return Pointer to the new vector.
 */
t_vector		*vector_alloc(double x, double y);

/**
 * @brief Create a new edge allocated on the heap. The returned edge can be
 * freed with the free() function.
 * @param x
 * @param y
 * @return Pointer to the new edge.
 */
t_edge			*edge_alloc(t_vector start, t_vector end);

/**
 * @brief Create a copy of a vector. Can be used to create a copy on the heap
 * of a vector on the stack.
 * @param a
 * @return
 */
t_vector		*vector_copy(t_vector a);

/**
 * @brief Basic initialization of the t_data structure.
 * @return Data structure with the MLX-related fields initialized.
 */
t_data			*init_data(void);

/**
 * @brief Initialize the player's position, direction, and rays.
 * @param data The data structure to modify.
 * @param pos The player's position.
 * @param angle The player's angle in radians.
 */
void			init_player(t_data *data, t_vector pos, double angle);

/**
 * @brief Create a new image from a cropped region of an existing texture.
 * @param texture The texture to crop.
 * @param origin The origin of the crop region.
 * @param size The size of the crop region.
 * @return An image of the cropped region.
 */
mlx_image_t 	*cropped_texture(mlx_t *mlx, mlx_texture_t *texture, t_vector origin, t_vector size);

mlx_image_t *scale_image(mlx_image_t *img, t_vector scale);

#endif //CUB3D_H
