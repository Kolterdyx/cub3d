
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
 */
typedef struct s_edge
{
	t_vector	start;
	t_vector	end;
}				t_edge;

/**
 * @brief Main structure for holding global data.
 *
 * @param mlx The mlx instance.
 * @param img The image to draw to.
 * @param edges Double linked list of edges to intersect.
 * @param player_pos The player's position.
 * @param player_edges The player's edges that will be used for ray casting.
 *
 */
typedef struct t_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_list		*edges;

	t_vector	player_pos;
	t_list		*player_edges;
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

#endif //CUB3D_H
