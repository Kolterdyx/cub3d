
# Cub3D ([subject](en.subject.cub3d.pdf))

## Level storage

After parsing the map file, we need a useful way to store all the level data.
Each wall is a square, so we could store the level as a 2D array of integers.
However, this will make it difficult to find the intersections between the rays
and the walls. Instead, we can store the level as a double linked list of edges.
Each wall character represents a square, so we can store the edges of the square
instead of the center of the square itself, which will allow us to iterate over
the edges of the level directly as we cast rays.

Each edge is stored as a `t_edge` struct, which contains the coordinates of the
start and end points of the edge represented with 2D vectors. This struct is in turn stored in a `t_list` node.
We can access the linked list of edges using the `s_data::edges` pointer.

```c
typedef struct s_edge
{
    t_vector    start;
    t_vector    end;
}               t_edge;
```

Similarly, we can use the `t_edge` struct to store the rays that we cast. Each
ray is represented by a `t_vector` struct, which contains a unit vector pointing in the
relative direction of the ray. On runtime, this vector is rotated by the player's
rotation angle, and then scaled to the length of the ray. This vector can then be used
to create a `t_edge` struct at runtime, which can easily be compared against other edges
in the level.

## Raycasting

Raycasting is the process of casting rays from the player's position in the level, and
checking for intersections with the level's edges. The easiest way to do this is, for each
ray that we cast, to iterate over all the edges in the level and check for intersections. If we
find multiple, we can choose the closest one. This is the method that we will use in this project.
However, because this is not really efficient, we need to reduce the number of edges in the level.
When we load the level, we can cull all the edges that won't ever be visible to the player. This 
can easily be achieved by preprocessing the level and removing all the edges that are considered "hidden".

```

A row of tiles before culling

----------------
|  ||  ||  ||  |
----------------

A row of tiles after culling

----------------
|              |
----------------

```

## Rendering

[Raycast Visibility Algorithm](https://lodev.org/cgtutor/raycasting.html#RayCastingVisibilityAlgorithm)

# Building

This project is compatible with Linux and MacOS. To build the project, on 
Linux, you will need to install the required [MLX42 dependencies]
(https://github.com/codam-coding-college/MLX42#for-linux).

On MacOS, you should only need to install `glfw` or `glfw3` using `brew`.

```bash
brew install glfw
```

To build the project, run `make` in the root directory of the project.
