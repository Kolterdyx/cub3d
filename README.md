
# Cub3D ([subject](en.subject.cub3d.pdf))

## Level storage

After parsing the map file, we need a useful way to store all the level data.
Each wall is a square, so we could store the level as a 2D array of integers.
However, this will make it difficult to find the intersections between the rays
and the walls. Instead, we can store the level as a double linked list of wall_edges.
Each wall character represents a square, so we can store the wall_edges of the square
instead of the center of the square itself, which will allow us to iterate over
the wall_edges of the level directly as we cast rays.

Each edge is stored as a `t_edge` struct, which contains the coordinates of the
start and end points of the edge represented with 2D vectors. This struct is in turn stored in a `t_list` node.
We can access the linked list of wall_edges using the `s_data::wall_edges` pointer.

```c
typedef struct s_edge
{
    t_vec    start;
    t_vec    end;
}               t_edge;
```

Similarly, we can use the `t_edge` struct to store the rays that we cast. Each
ray is represented by a `t_vec` struct, which contains a unit vector pointing in the
relative direction of the ray. On runtime, this vector is rotated by the player's
rotation angle, and then scaled to the length of the ray. This vector can then be used
to create a `t_edge` struct at runtime, which can easily be compared against other wall_edges
in the level.

## Raycasting

Raycasting is the process of casting rays from the player's position in the level, and
checking for intersections with the level's wall_edges. The easiest way to do this is, for each
ray that we cast, to iterate over all the wall_edges in the level and check for intersections. If we
find multiple, we can choose the closest one. This is the method that we will use in this project.
However, because this is not really efficient, we need to reduce the number of wall_edges in the level.
When we load the level, we can cull all the wall_edges that won't ever be visible to the player. This 
can easily be achieved by preprocessing the level and removing all the wall_edges that are considered "hidden".

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

# Other stuff

Map format. Text between curly braces is an explanation of the format, and is not part of the map.

```
{elements of the map in any order}
NO{1 or more spaces}./path_to_the_north_texture
{0 or more empty lines}
SO{1 or more spaces}./path_to_the_south_texture
{0 or more empty lines}
WE{1 or more spaces}./path_to_the_west_texture
{0 or more empty lines}
EA{1 or more spaces}./path_to_the_east_texture
{0 or more empty lines}
SP{1 or more spaces}./path_to_the_sprite_texture{1 or more spaces}width{1 or more spaces}height{1 or more spaces}number_of_sprites
{0 or more empty lines}
F{1 or more spaces}220,100,0
{0 or more empty lines}
C{1 or more spaces}225,30,0
{0 or more empty lines}

{map at the end}
{for simplicity's sake, we can interpret spaces as zeros when building the 
map except for map validation}
        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

Here is an example of a valid map:

```
NO  ./assets/north_test.png

SO ./assets/south_test.png
WE    ./assets/west_test.png


EA   ./assets/east_test.png




F    220,100,0

C  225,30,0





        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

# Textures

Textures are stored in a `mlx_texture_t *` array (`t_data.textures`). The position of these textures in the array is important, as they are used to determine which texture to use when rendering a wall. The order of the textures in the array is as follows:

- North texture (NO) - `t_data.textures[0]`
- West texture (WE)  - `t_data.textures[1]`
- South texture (SO) - `t_data.textures[2]`
- East texture (EA)  - `t_data.textures[3]`
- Door texture       - `t_data.textures[4]`
- `undefined beyond here`