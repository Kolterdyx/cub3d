
#include "cub3d.h"

void	loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	(void)data;
}

t_data	*init_data(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 0);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	return (data);
}

int	main(void)
{
	t_data	*data;

	data = init_data();
	mlx_loop_hook(data->mlx, loop, data);
	mlx_key_hook(data->mlx, key_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}
