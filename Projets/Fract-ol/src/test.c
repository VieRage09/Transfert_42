#include "../fractol.h"

int	handle_key(int keycode)
{
	ft_printf("%d\n", keycode);
	return 1;
}

int	main()
{
	t_global	*s_glb;
	t_reso		s_reso;

	set_reso(&s_reso, 960, 540);
	s_glb = new_global(new_cpx_pt(0, 0), &s_reso, 50,
				bicolor_grad(new_color(0, 0, 0), new_color(50, 50, 50), 50));

	mlx_hook(s_glb->s_mlx->win, 3, 1L << 1, handle_key, s_glb);
	mlx_loop(s_glb->s_mlx->mlx);
	return 0;
}
